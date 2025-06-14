#include "DebugUART.hpp"
#include "GameBoard.hpp"

#ifdef __cplusplus
#include <cstdarg>
#else
#include <stdarg.h>
#endif

UART_HandleTypeDef* DebugUART::m_uart = nullptr;
char DebugUART::buffer[256];

void DebugUART::initialize(UART_HandleTypeDef* uart) {
    m_uart = uart;
    print("Debug UART initialized\r\n");
}

void DebugUART::print(const char* message) {
    if (m_uart != nullptr) {
        HAL_UART_Transmit(m_uart, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);
    }
}

void DebugUART::printf(const char* format, ...) {
    if (m_uart == nullptr) return;
    
    va_list args;
    va_start(args, format);
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    if (len > 0) {
        HAL_UART_Transmit(m_uart, (uint8_t*)buffer, len, HAL_MAX_DELAY);
    }
}

void DebugUART::printBoard(const GameBoard& board) {
    if (m_uart == nullptr) return;
    
    print("+------+------+------+------+\r\n");
    for (int row = 0; row < 4; row++) {
        print("|");
        for (int col = 0; col < 4; col++) {
            uint16_t value = board.getTile(row, col);
            if (value == 0) {
                print("      |");
            } else {
                printf("%5d |", value);
            }
        }
        print("\r\n+------+------+------+------+\r\n");
    }
    printf("Score: %lu\r\n\r\n", board.getScore());
}

void DebugUART::printGyroData(int16_t x, int16_t y, int16_t z) {
    printf("Gyro: X=%d, Y=%d, Z=%d\r\n", x, y, z);
}

// C interface implementations
extern "C" {
    void debug_print(const char* message) {
        DebugUART::print(message);
    }
    
    void debug_printf(const char* format, ...) {
        if (DebugUART::m_uart == nullptr) return;
        
        va_list args;
        va_start(args, format);
        int len = vsnprintf(DebugUART::buffer, sizeof(DebugUART::buffer), format, args);
        va_end(args);
        
        if (len > 0) {
            HAL_UART_Transmit(DebugUART::m_uart, (uint8_t*)DebugUART::buffer, len, HAL_MAX_DELAY);
        }
    }
}
