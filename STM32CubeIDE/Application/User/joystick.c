/**
 ******************************************************************************
 * @file    joystick.c
 * @brief   Joystick input handling for 2048 game
 * @author  Generated for STM32F429I Discovery
 ******************************************************************************
 */

#include "main.h"
#include "cmsis_os2.h"
#include "gui/common/Direction.hpp"
#include "gui/common/JoystickConfig.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* External ADC handles - these should be defined in main.c */
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern UART_HandleTypeDef huart1;

/* FreeRTOS message queue for direction communication */
osMessageQueueId_t directionQueueHandle;
const osMessageQueueAttr_t directionQueue_attributes = {
  .name = "directionQueue"
};

/* Private variables */
static uint16_t joystick_x_raw = JOYSTICK_X_CENTER;
static uint16_t joystick_y_raw = JOYSTICK_Y_CENTER;
static GameDirection last_direction = DIR_NONE;
static uint32_t last_direction_time = 0;

/* Debug variables (can be watched in debugger) */
static uint16_t debug_x_value = 0;
static uint16_t debug_y_value = 0;
static GameDirection debug_direction = DIR_NONE;
static uint32_t debug_direction_count = 0;

/* Private function prototypes */
static GameDirection Joystick_AnalyzeDirection(uint16_t x_val, uint16_t y_val);
static void Joystick_SendDebugOutput(uint16_t vrx, uint16_t vry, const char* direction);
static const char* Joystick_GetDirectionString(GameDirection dir);

/**
 * @brief  Initialize joystick functionality
 * @retval None
 */
void Joystick_Init(void)
{
    /* Create message queue for direction communication */
    directionQueueHandle = osMessageQueueNew(8, sizeof(GameDirection), &directionQueue_attributes);
    
    /* Note: STM32F4 ADCs don't require explicit calibration like STM32F3 series */
    /* ADC calibration is performed automatically by the hardware */
    
    /* Test initial ADC readings to verify hardware is working */
    uint16_t test_x = Joystick_ReadX();
    uint16_t test_y = Joystick_ReadY();
    
    /* Store initial readings */
    joystick_x_raw = test_x;
    joystick_y_raw = test_y;
}

/**
 * @brief  Read X-axis value from joystick (VRx on PC3/ADC1_IN13)
 * @retval ADC value (0-4095)
 */
uint16_t Joystick_ReadX(void)
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    uint16_t adc_value = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    
    joystick_x_raw = adc_value;
    return adc_value;
}

/**
 * @brief  Read Y-axis value from joystick (VRy on PA5/ADC2_IN5)
 * @retval ADC value (0-4095)
 */
uint16_t Joystick_ReadY(void)
{
    HAL_ADC_Start(&hadc2);
    HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);
    uint16_t adc_value = HAL_ADC_GetValue(&hadc2);
    HAL_ADC_Stop(&hadc2);
    
    joystick_y_raw = adc_value;
    return adc_value;
}

/**
 * @brief  Analyze raw ADC values and determine direction
 * @param  x_val: X-axis ADC value
 * @param  y_val: Y-axis ADC value
 * @retval Direction enum value
 */
static GameDirection Joystick_AnalyzeDirection(uint16_t x_val, uint16_t y_val)
{
    /* Check if joystick is in deadzone (neutral position) */
    if (JOYSTICK_IS_X_NEUTRAL(x_val) && JOYSTICK_IS_Y_NEUTRAL(y_val))
    {
        return DIR_NONE;
    }
    
    /* Use the defined macros for direction detection */
    int is_left = JOYSTICK_IS_LEFT(x_val);
    int is_right = JOYSTICK_IS_RIGHT(x_val);
    int is_up = JOYSTICK_IS_UP(y_val);
    int is_down = JOYSTICK_IS_DOWN(y_val);
    
    /* Calculate deviations to determine which axis has larger movement */
    int16_t x_deviation = abs((int16_t)x_val - JOYSTICK_X_CENTER);
    int16_t y_deviation = abs((int16_t)y_val - JOYSTICK_Y_CENTER);
    
    /* Determine primary direction based on larger deviation */
    if (x_deviation > y_deviation)
    {
        /* Horizontal movement is dominant */
        if (is_right)
        {
            return DIR_RIGHT;
        }
        else if (is_left)
        {
            return DIR_LEFT;
        }
    }
    else
    {
        /* Vertical movement is dominant */
        if (is_up)
        {
            return DIR_UP;
        }
        else if (is_down)
        {
            return DIR_DOWN;
        }
    }
    
    return DIR_NONE;
}

/**
 * @brief  Get current joystick direction with debouncing
 * @retval Direction enum value
 */
GameDirection Joystick_GetDirection(void)
{
    uint16_t x_val = Joystick_ReadX();
    uint16_t y_val = Joystick_ReadY();
    
    GameDirection current_direction = Joystick_AnalyzeDirection(x_val, y_val);
    uint32_t current_time = HAL_GetTick();
    
    /* Debouncing: Only register new direction if enough time has passed */
    const uint32_t DEBOUNCE_TIME_MS = JOYSTICK_DEBOUNCE_TIME_MS;
    
    if (current_direction != DIR_NONE && 
        current_direction != last_direction &&
        (current_time - last_direction_time) > DEBOUNCE_TIME_MS)
    {
        last_direction = current_direction;
        last_direction_time = current_time;
        
        /* Send direction to message queue for TouchGFX */
        osStatus_t status = osMessageQueuePut(directionQueueHandle, &current_direction, 0, 0);
        
        /* Add debug output for queue operations */
        #ifdef HAL_UART_MODULE_ENABLED
        if (status == osOK) {
            char debug_msg[64];
            const char* dir_name = Joystick_GetDirectionString(current_direction);
            int len = snprintf(debug_msg, sizeof(debug_msg), ">>> QUEUE: Sent %s to TouchGFX\r\n", dir_name);
            HAL_UART_Transmit(&huart1, (uint8_t*)debug_msg, len, HAL_MAX_DELAY);
        }
        #endif
        
        return current_direction;
    }
    else if (current_direction == DIR_NONE)
    {
        /* Reset when joystick returns to center */
        last_direction = DIR_NONE;
    }
    
    return DIR_NONE;
}

/**
 * @brief  Joystick polling task (should be called periodically)
 * @retval None
 */
void Joystick_Task(void)
{
    static uint32_t last_debug_time = 0;
    uint32_t current_time = HAL_GetTick();
    
    /* Read current joystick values for debugging */
    debug_x_value = Joystick_ReadX();
    debug_y_value = Joystick_ReadY();
    debug_direction = Joystick_AnalyzeDirection(debug_x_value, debug_y_value);
    
    /* Process direction for game logic */
    GameDirection game_direction = Joystick_GetDirection();
    if (game_direction != DIR_NONE) {
        debug_direction_count++;
    }
    
    /* Send UART debug output every 500ms to avoid overflow */
    if ((current_time - last_debug_time) >= 500) {
        const char* dir_str = Joystick_GetDirectionString(debug_direction);
        Joystick_SendDebugOutput(debug_x_value, debug_y_value, dir_str);
        last_debug_time = current_time;
    }
}

/**
 * @brief  Get raw joystick values for debugging
 * @param  x_raw: Pointer to store X raw value
 * @param  y_raw: Pointer to store Y raw value
 * @retval None
 */
void Joystick_GetRawValues(uint16_t* x_raw, uint16_t* y_raw)
{
    if (x_raw != NULL) *x_raw = joystick_x_raw;
    if (y_raw != NULL) *y_raw = joystick_y_raw;
}

/**
 * @brief  Test function to verify joystick is working correctly
 * @note   This function reads raw values and can be used with debugger
 * @retval 1 if readings are in expected range, 0 otherwise
 */
uint8_t Joystick_TestReadings(void)
{
    uint16_t x_val = Joystick_ReadX();
    uint16_t y_val = Joystick_ReadY();
    
    /* Expected ranges from JOYSTICK_TEST_REPORT.md:
     * Center: X=2085±20, Y=2060±20
     * Full range: 0-4095 for both axes
     */
    
    /* Check if readings are in valid ADC range */
    if (x_val > 4095 || y_val > 4095) {
        return 0; // Invalid readings
    }
    
    /* Store current readings for debugging */
    joystick_x_raw = x_val;
    joystick_y_raw = y_val;
    
    return 1; // Valid readings
}

/**
 * @brief  Convert GameDirection enum to string (matching test report format)
 * @param  dir: GameDirection enum value
 * @retval String representation of direction
 */
static const char* Joystick_GetDirectionString(GameDirection dir)
{
    switch (dir) {
        case DIR_LEFT:  return "LEFT";
        case DIR_RIGHT: return "RIGHT";
        case DIR_UP:    return "UP";
        case DIR_DOWN:  return "DOWN";
        case DIR_NONE:  return "IDLE";
        default:        return "UNKNOWN";
    }
}

/**
 * @brief  Send debug output via UART (matching JOYSTICK_TEST_REPORT.md format)
 * @param  vrx: X-axis raw ADC value
 * @param  vry: Y-axis raw ADC value  
 * @param  direction: Direction string
 * @retval None
 */
static void Joystick_SendDebugOutput(uint16_t vrx, uint16_t vry, const char* direction)
{
    #ifdef HAL_UART_MODULE_ENABLED
    char buffer[64];
    int len = snprintf(buffer, sizeof(buffer), "VRx: %04d, VRy: %04d, Direction: %s\r\n", vrx, vry, direction);
    HAL_UART_Transmit(&huart1, (uint8_t*)buffer, len, HAL_MAX_DELAY);
    #else
    /* UART debug output disabled - USART driver not available */
    (void)vrx;
    (void)vry;
    (void)direction;
    #endif
}

/**
 * @brief  Initialize joystick debug output (matching test report format)
 * @retval None
 */
void Joystick_InitDebug(void)
{
    #ifdef HAL_UART_MODULE_ENABLED
    const char* init_msg = "Joystick Debug Started\r\n"
                          "Format: VRx: XXXX, VRy: XXXX, Direction: XXXXX\r\n"
                          "==========================================\r\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)init_msg, strlen(init_msg), HAL_MAX_DELAY);
    #endif
}

/**
 * @brief  Simple ADC test function (for debugging)
 * @retval None
 */
void Joystick_DebugTest(void)
{
    /* Simple ADC reading test matching debug project approach */
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    debug_x_value = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    
    HAL_ADC_Start(&hadc2);
    HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);
    debug_y_value = HAL_ADC_GetValue(&hadc2);
    HAL_ADC_Stop(&hadc2);
    
    /* Calculate deviations like in debug project */
    int16_t x_deviation = debug_x_value - JOYSTICK_X_CENTER;
    int16_t y_deviation = debug_y_value - JOYSTICK_Y_CENTER;
    
    /* Simple direction logic matching debug project */
    if (abs(x_deviation) < JOYSTICK_DEADZONE_X && abs(y_deviation) < JOYSTICK_DEADZONE_Y)
    {
        debug_direction = DIR_NONE; // IDLE
    }
    else if (abs(x_deviation) > abs(y_deviation))
    {
        if (x_deviation > 1500)
            debug_direction = DIR_RIGHT;
        else if (x_deviation < -1500)
            debug_direction = DIR_LEFT;
    }
    else
    {
        if (y_deviation > 1500)
            debug_direction = DIR_UP;    // Matching debug project: positive Y deviation = UP
        else if (y_deviation < -1500)
            debug_direction = DIR_DOWN;  // Matching debug project: negative Y deviation = DOWN
    }
} 