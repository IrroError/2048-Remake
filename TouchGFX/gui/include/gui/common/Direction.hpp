#ifndef DIRECTION_HPP
#define DIRECTION_HPP

#include "gui/common/JoystickConfig.hpp"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Direction enumeration for 2048 game input
 * These values correspond to joystick movements
 */
typedef enum {
    DIR_NONE = 0,    ///< No direction/neutral position
    DIR_LEFT,        ///< Joystick moved left
    DIR_RIGHT,       ///< Joystick moved right  
    DIR_UP,          ///< Joystick moved up
    DIR_DOWN         ///< Joystick moved down
} Direction;

/**
 * @brief ADC threshold values for joystick direction detection
 * These values are imported from JoystickConfig.hpp
 */
#define JOYSTICK_CENTER_VALUE       JOYSTICK_X_CENTER    // Center position
#define JOYSTICK_DEADZONE           JOYSTICK_DEADZONE_X  // Deadzone around center
#define JOYSTICK_THRESHOLD_LOW      JOYSTICK_THRESHOLD_LOW_X
#define JOYSTICK_THRESHOLD_HIGH     JOYSTICK_THRESHOLD_HIGH_X

/**
 * @brief ADC channel definitions for joystick
 */
#define JOYSTICK_ADC_X_CHANNEL      ADC_CHANNEL_13  // PC3 - VRx
#define JOYSTICK_ADC_Y_CHANNEL      ADC_CHANNEL_5   // PA5 - VRy

/**
 * @brief Function prototypes for joystick handling
 */
Direction Joystick_GetDirection(void);
void Joystick_Init(void);
uint16_t Joystick_ReadX(void);
uint16_t Joystick_ReadY(void);

#ifdef __cplusplus
}
#endif

#endif /* DIRECTION_HPP */ 