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

/* External ADC handles - these should be defined in main.c */
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;

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

/* Private function prototypes */
static GameDirection Joystick_AnalyzeDirection(uint16_t x_val, uint16_t y_val);

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
    
    /* Calculate distance from center for both axes */
    int16_t x_distance = x_val - JOYSTICK_X_CENTER;
    int16_t y_distance = y_val - JOYSTICK_Y_CENTER;
    
    /* Apply inversion if configured */
    #if JOYSTICK_INVERT_X
    x_distance = -x_distance;
    #endif
    
    #if JOYSTICK_INVERT_Y
    y_distance = -y_distance;
    #endif
    
    /* Determine primary direction based on larger displacement */
    if (abs(x_distance) > abs(y_distance))
    {
        /* X-axis movement is dominant */
        if (x_distance > 0)
            return DIR_RIGHT;
        else
            return DIR_LEFT;
    }
    else
    {
        /* Y-axis movement is dominant */
        if (y_distance > 0)
            return DIR_DOWN;   // Assuming higher ADC value = joystick down
        else
            return DIR_UP;     // Assuming lower ADC value = joystick up
    }
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
        osMessageQueuePut(directionQueueHandle, &current_direction, 0, 0);
        
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
    /* This function should be called from a FreeRTOS task or timer */
    Joystick_GetDirection();
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