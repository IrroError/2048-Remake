#ifndef JOYSTICK_CONFIG_H
#define JOYSTICK_CONFIG_H

/**
 * @brief Joystick Configuration for STM32F429I Discovery Board
 * 
 * Hardware Configuration:
 * - VRx (X-axis): PC3 -> ADC1_IN13
 * - VRy (Y-axis): PA5 -> ADC2_IN5
 * - VCC: 3.3V
 * - GND: Ground
 * - SW: Can be connected to PA0, PA1, or PA2 (not configured yet)
 */

/* Joystick calibration values - adjust these based on your hardware */
#define JOYSTICK_X_MIN          100     // Minimum X value (left)
#define JOYSTICK_X_MAX          3900    // Maximum X value (right)
#define JOYSTICK_X_CENTER       2048    // Center X value (neutral)

#define JOYSTICK_Y_MIN          100     // Minimum Y value (up)
#define JOYSTICK_Y_MAX          3900    // Maximum Y value (down)
#define JOYSTICK_Y_CENTER       2048    // Center Y value (neutral)

/* Deadzone configuration */
#define JOYSTICK_DEADZONE_X     200     // X-axis deadzone
#define JOYSTICK_DEADZONE_Y     200     // Y-axis deadzone

/* Movement thresholds */
#define JOYSTICK_THRESHOLD_LOW_X    (JOYSTICK_X_CENTER - JOYSTICK_DEADZONE_X)
#define JOYSTICK_THRESHOLD_HIGH_X   (JOYSTICK_X_CENTER + JOYSTICK_DEADZONE_X)
#define JOYSTICK_THRESHOLD_LOW_Y    (JOYSTICK_Y_CENTER - JOYSTICK_DEADZONE_Y)
#define JOYSTICK_THRESHOLD_HIGH_Y   (JOYSTICK_Y_CENTER + JOYSTICK_DEADZONE_Y)

/* Timing configuration */
#define JOYSTICK_DEBOUNCE_TIME_MS   150    // Debounce time in milliseconds
#define JOYSTICK_POLL_INTERVAL_MS   50     // Polling interval for joystick task

/* Direction mapping - adjust if joystick is oriented differently */
#define JOYSTICK_INVERT_X       0       // Set to 1 to invert X-axis
#define JOYSTICK_INVERT_Y       0       // Set to 1 to invert Y-axis

/**
 * @brief Calibration helper macros
 */
#define JOYSTICK_IS_X_NEUTRAL(x)  ((x) > JOYSTICK_THRESHOLD_LOW_X && (x) < JOYSTICK_THRESHOLD_HIGH_X)
#define JOYSTICK_IS_Y_NEUTRAL(y)  ((y) > JOYSTICK_THRESHOLD_LOW_Y && (y) < JOYSTICK_THRESHOLD_HIGH_Y)

#define JOYSTICK_IS_LEFT(x)       ((x) < JOYSTICK_THRESHOLD_LOW_X)
#define JOYSTICK_IS_RIGHT(x)      ((x) > JOYSTICK_THRESHOLD_HIGH_X)
#define JOYSTICK_IS_UP(y)         ((y) < JOYSTICK_THRESHOLD_LOW_Y)
#define JOYSTICK_IS_DOWN(y)       ((y) > JOYSTICK_THRESHOLD_HIGH_Y)

#endif /* JOYSTICK_CONFIG_H */ 