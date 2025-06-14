#ifndef DEBUG_UART_HPP
#define DEBUG_UART_HPP

#include "main.h"

#ifdef __cplusplus
#include <cstdio>
#include <cstring>
#else
#include <stdio.h>
#include <string.h>
#endif

class DebugUART {
public:
    static void initialize(UART_HandleTypeDef* uart);
    static void print(const char* message);
    static void printf(const char* format, ...);
    static void printBoard(const class GameBoard& board);
    static void printGyroData(int16_t x, int16_t y, int16_t z);
    
    // Public access for C interface
    static UART_HandleTypeDef* m_uart;
    static char buffer[256];
    
private:
    // Private helper methods if needed
};

// C interface for use in C files
#ifdef __cplusplus
extern "C" {
#endif

void debug_print(const char* message);
void debug_printf(const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif // DEBUG_UART_HPP
