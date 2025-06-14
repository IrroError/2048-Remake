#include "Gyroscope.hpp"

// Constructor
Gyroscope::Gyroscope(SPI_HandleTypeDef* spiHandle, GPIO_TypeDef* csPort, uint16_t csPin)
    : m_spi(spiHandle), m_csPort(csPort), m_csPin(csPin),
      m_movementThreshold(1000), m_offsetX(0), m_offsetY(0), m_offsetZ(0) {
}

bool Gyroscope::initialize() {
    // Check if the gyroscope is connected
    if (!isConnected()) {
        return false;
    }
    
    // Configure CTRL_REG1: Power on, data rate 95Hz, bandwidth 25Hz, enable all axes
    writeRegister(L3GD20_CTRL_REG1, 
                  L3GD20_MODE_ACTIVE | 
                  L3GD20_OUTPUT_DATARATE_1 | 
                  L3GD20_AXES_ENABLE | 
                  L3GD20_BANDWIDTH_1);
    
    // Configure CTRL_REG4: Full scale ±250 dps, continuous block data update
    writeRegister(L3GD20_CTRL_REG4, 
                  L3GD20_FULLSCALE_250 | 
                  L3GD20_BlockDataUpdate_Continous);
    
    // Small delay to let the sensor stabilize
    HAL_Delay(10);
    
    // Calibrate the gyroscope
    calibrate();
    
    return true;
}

bool Gyroscope::isConnected() {
    uint8_t whoAmI = readRegister(L3GD20_WHO_AM_I);
    return (whoAmI == 0xD4); // L3GD20 WHO_AM_I value
}

bool Gyroscope::readGyroData(int16_t* x, int16_t* y, int16_t* z) {
    uint8_t buffer[6];
    
    // Read 6 bytes starting from OUT_X_L
    readMultipleRegisters(L3GD20_OUT_X_L, buffer, 6);
    
    // Combine high and low bytes for each axis
    *x = (int16_t)((buffer[1] << 8) | buffer[0]) - m_offsetX;
    *y = (int16_t)((buffer[3] << 8) | buffer[2]) - m_offsetY;
    *z = (int16_t)((buffer[5] << 8) | buffer[4]) - m_offsetZ;
    
    return true;
}

GameDirection Gyroscope::getTiltDirection() {
    int16_t x, y, z;
    
    if (!readGyroData(&x, &y, &z)) {
        return GameDirection::NONE;
    }
    
    // Check which axis has the strongest movement
    // Note: You may need to adjust these based on your board orientation
    
    // X-axis: Left/Right movement
    if (x > m_movementThreshold) {
        return GameDirection::RIGHT;
    } else if (x < -m_movementThreshold) {
        return GameDirection::LEFT;
    }
    
    // Y-axis: Forward/Backward movement  
    if (y > m_movementThreshold) {
        return GameDirection::UP;
    } else if (y < -m_movementThreshold) {
        return GameDirection::DOWN;
    }
    
    return GameDirection::NONE;
}

void Gyroscope::setThresholds(int16_t threshold) {
    m_movementThreshold = threshold;
}

void Gyroscope::calibrate() {
    const uint8_t samples = 100;
    int32_t sumX = 0, sumY = 0, sumZ = 0;
    
    // Take multiple readings to calculate offset
    for (uint8_t i = 0; i < samples; i++) {
        int16_t x, y, z;
        uint8_t buffer[6];
        
        readMultipleRegisters(L3GD20_OUT_X_L, buffer, 6);
        
        x = (int16_t)((buffer[1] << 8) | buffer[0]);
        y = (int16_t)((buffer[3] << 8) | buffer[2]);
        z = (int16_t)((buffer[5] << 8) | buffer[4]);
        
        sumX += x;
        sumY += y;
        sumZ += z;
        
        HAL_Delay(10); // Small delay between readings
    }
    
    // Calculate average offsets
    m_offsetX = sumX / samples;
    m_offsetY = sumY / samples;
    m_offsetZ = sumZ / samples;
}

void Gyroscope::writeRegister(uint8_t reg, uint8_t value) {
    uint8_t txData[2];
    
    txData[0] = reg;
    txData[1] = value;
    
    csLow();
    HAL_SPI_Transmit(m_spi, txData, 2, HAL_MAX_DELAY);
    csHigh();
}

uint8_t Gyroscope::readRegister(uint8_t reg) {
    uint8_t txData = reg | 0x80; // Set read bit
    uint8_t rxData = 0;
    
    csLow();
    HAL_SPI_Transmit(m_spi, &txData, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(m_spi, &rxData, 1, HAL_MAX_DELAY);
    csHigh();
    
    return rxData;
}

void Gyroscope::readMultipleRegisters(uint8_t reg, uint8_t* buffer, uint8_t length) {
    uint8_t txData = reg | 0x80 | 0x40; // Set read bit and multiple read bit
    
    csLow();
    HAL_SPI_Transmit(m_spi, &txData, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(m_spi, buffer, length, HAL_MAX_DELAY);
    csHigh();
}

void Gyroscope::csLow() {
    HAL_GPIO_WritePin(m_csPort, m_csPin, GPIO_PIN_RESET);
}

void Gyroscope::csHigh() {
    HAL_GPIO_WritePin(m_csPort, m_csPin, GPIO_PIN_SET);
}
