#ifndef GYROSCOPE_HPP
#define GYROSCOPE_HPP

#include "main.h"
#include "GameBoard.hpp"

// L3GD20 Gyroscope Register Addresses
#define L3GD20_WHO_AM_I      0x0F
#define L3GD20_CTRL_REG1     0x20
#define L3GD20_CTRL_REG2     0x21
#define L3GD20_CTRL_REG3     0x22
#define L3GD20_CTRL_REG4     0x23
#define L3GD20_CTRL_REG5     0x24
#define L3GD20_REFERENCE     0x25
#define L3GD20_OUT_TEMP      0x26
#define L3GD20_STATUS_REG    0x27
#define L3GD20_OUT_X_L       0x28
#define L3GD20_OUT_X_H       0x29
#define L3GD20_OUT_Y_L       0x2A
#define L3GD20_OUT_Y_H       0x2B
#define L3GD20_OUT_Z_L       0x2C
#define L3GD20_OUT_Z_H       0x2D

// L3GD20 Configuration Values
#define L3GD20_MODE_POWERDOWN    0x00
#define L3GD20_MODE_ACTIVE       0x08
#define L3GD20_OUTPUT_DATARATE_1 0x00
#define L3GD20_OUTPUT_DATARATE_2 0x40
#define L3GD20_OUTPUT_DATARATE_3 0x80
#define L3GD20_OUTPUT_DATARATE_4 0xC0
#define L3GD20_AXES_ENABLE       0x07
#define L3GD20_BANDWIDTH_1       0x00
#define L3GD20_BANDWIDTH_2       0x10
#define L3GD20_BANDWIDTH_3       0x20
#define L3GD20_BANDWIDTH_4       0x30

#define L3GD20_FULLSCALE_250     0x00
#define L3GD20_FULLSCALE_500     0x10
#define L3GD20_FULLSCALE_2000    0x20

#define L3GD20_BlockDataUpdate_Continous 0x00
#define L3GD20_BlockDataUpdate_Single    0x80

#define L3GD20_BLE_LSB           0x00
#define L3GD20_BLE_MSB           0x40

#define L3GD20_BOOT_NORMALMODE   0x00
#define L3GD20_BOOT_REBOOTMEMORY 0x80

class Gyroscope {
public:
    Gyroscope(SPI_HandleTypeDef* spiHandle, GPIO_TypeDef* csPort, uint16_t csPin);
    ~Gyroscope() = default;
    
    // Initialization
    bool initialize();
    bool isConnected();
      // Data reading
    bool readGyroData(int16_t* x, int16_t* y, int16_t* z);
    GameDirection getTiltDirection();
    
    // Configuration
    void setThresholds(int16_t threshold);
    void calibrate();
    
private:
    SPI_HandleTypeDef* m_spi;
    GPIO_TypeDef* m_csPort;
    uint16_t m_csPin;
    
    // Thresholds for movement detection
    int16_t m_movementThreshold;
    
    // Calibration offsets
    int16_t m_offsetX;
    int16_t m_offsetY;
    int16_t m_offsetZ;
    
    // SPI Communication
    void writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);
    void readMultipleRegisters(uint8_t reg, uint8_t* buffer, uint8_t length);
    
    // CS control
    void csLow();
    void csHigh();
};

#endif // GYROSCOPE_HPP
