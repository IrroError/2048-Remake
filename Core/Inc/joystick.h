/**
 ******************************************************************************
 * @file    joystick.h
 * @brief   Header for joystick.c file
 * @author  Generated for STM32F429I Discovery
 ******************************************************************************
 */

#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os2.h"
#include "gui/common/Direction.hpp"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief  Initialize joystick functionality
 * @retval None
 */
void Joystick_Init(void);

/**
 * @brief  Read X-axis value from joystick
 * @retval ADC value (0-4095)
 */
uint16_t Joystick_ReadX(void);

/**
 * @brief  Read Y-axis value from joystick
 * @retval ADC value (0-4095)
 */
uint16_t Joystick_ReadY(void);

/**
 * @brief  Get current joystick direction with debouncing
 * @retval GameDirection enum value
 */
GameDirection Joystick_GetDirection(void);

/**
 * @brief  Joystick polling task (should be called periodically)
 * @retval None
 */
void Joystick_Task(void);

/**
 * @brief  Get raw joystick values for debugging
 * @param  x_raw: Pointer to store X raw value
 * @param  y_raw: Pointer to store Y raw value
 * @retval None
 */
void Joystick_GetRawValues(uint16_t* x_raw, uint16_t* y_raw);

/* Exported variables --------------------------------------------------------*/
extern osMessageQueueId_t directionQueueHandle;

#ifdef __cplusplus
}
#endif

#endif /* __JOYSTICK_H */ 