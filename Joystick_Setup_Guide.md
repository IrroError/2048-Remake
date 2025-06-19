# Joystick Setup Guide for 2048 Game

## Hardware Configuration

### STM32F429I Discovery Board Connections
```
Joystick Pin    ->    STM32 Pin    ->    Function
VCC             ->    3.3V          ->    Power supply
GND             ->    GND           ->    Ground
VRx (X-axis)    ->    PC3           ->    ADC1_IN13
VRy (Y-axis)    ->    PA5           ->    ADC2_IN5
SW (Button)     ->    PA0/PA1/PA2   ->    Optional (not implemented yet)
```

### Joystick Specifications
- **Operating Voltage**: 3.3V or 5V (3.3V recommended for STM32)
- **Output**: Analog voltage (0V to VCC)
- **Neutral Position**: ~VCC/2 (approximately 1.65V for 3.3V supply)
- **X-axis**: Left = 0V, Center = 1.65V, Right = 3.3V
- **Y-axis**: Up = 0V, Center = 1.65V, Down = 3.3V

## Software Implementation

### Files Created

1. **`TouchGFX/gui/include/gui/common/Direction.hpp`**
   - Defines the Direction enum (`DIR_LEFT`, `DIR_RIGHT`, `DIR_UP`, `DIR_DOWN`)
   - ADC channel definitions and references to JoystickConfig.hpp
   - Function prototypes for joystick handling

2. **`Core/Src/joystick.c`**
   - Complete joystick implementation
   - ADC reading functions
   - Direction analysis with debouncing
   - FreeRTOS message queue integration

3. **`Core/Inc/joystick.h`**
   - Header file for joystick functions
   - External variable declarations

4. **`TouchGFX/gui/include/gui/common/JoystickConfig.hpp`**
   - Configuration file for calibration values
   - Threshold and deadzone settings
   - Helper macros for direction detection

### Key Features

#### 1. **ADC Configuration**
- 12-bit resolution (0-4095 range)
- Software-triggered conversion
- Separate ADC instances for X and Y axes

#### 2. **Direction Detection Algorithm**
```c
// Deadzone check (neutral position)
if (x_val in deadzone && y_val in deadzone)
    return DIR_NONE;

// Determine dominant axis
if (abs(x_displacement) > abs(y_displacement))
    return (x_displacement > 0) ? DIR_RIGHT : DIR_LEFT;
else
    return (y_displacement > 0) ? DIR_DOWN : DIR_UP;
```

#### 3. **Debouncing**
- 150ms minimum time between direction changes
- Prevents multiple rapid fire inputs
- Smooth gameplay experience

#### 4. **FreeRTOS Integration**
- Dedicated joystick task (50ms polling)
- Message queue for direction communication
- Non-blocking communication with TouchGFX

## Configuration and Calibration

### 1. **Initial Setup**
The default configuration assumes:
- Center position: ADC value ~2048 (1.65V)
- Deadzone: ±300 ADC units around center
- Thresholds: 1748-2348 for neutral zone

### 2. **Calibration Process**
If your joystick doesn't work correctly:

1. **Test raw values**:
   ```c
   uint16_t x_raw, y_raw;
   Joystick_GetRawValues(&x_raw, &y_raw);
   // Use debugger or serial output to see values
   ```

2. **Adjust thresholds in `JoystickConfig.hpp`**:
   ```c
   #define JOYSTICK_X_CENTER       2048    // Your measured center value
   #define JOYSTICK_DEADZONE_X     200     // Adjust deadzone size
   ```

3. **Invert axes if needed**:
   ```c
   #define JOYSTICK_INVERT_X       1       // Invert X-axis
   #define JOYSTICK_INVERT_Y       1       // Invert Y-axis
   ```

### 3. **Pin Configuration in STM32CubeMX**
If you're regenerating the project, ensure:
- PC3 is configured as ADC1_IN13 (Analog mode)
- PA5 is configured as ADC2_IN5 (Analog mode)
- ADC1 and ADC2 are enabled with proper settings

## Integration Points

### 1. **Game Integration**
The joystick integrates with the existing game through:
- `Screen1View::tickEvent()` - Reads from message queue every 3 ticks
- Direction mapping to game moves
- Existing game logic remains unchanged

### 2. **Message Queue Flow**
```
Joystick Task → Direction Analysis → Message Queue → TouchGFX → Game Logic
```

### 3. **Task Priority**
- JoystickTask: Low priority (background polling)
- GUI_Task: Normal priority (TouchGFX)
- Input processing doesn't block GUI updates

## Troubleshooting

### Common Issues

1. **No Response**
   - Check ADC initialization
   - Verify pin connections
   - Test raw ADC values

2. **Wrong Directions**
   - Adjust inversion flags in config
   - Check axis mapping in hardware

3. **Too Sensitive/Not Sensitive Enough**
   - Adjust deadzone values
   - Modify threshold values
   - Change debounce timing

4. **Multiple Inputs**
   - Increase debounce time
   - Check for hardware noise
   - Verify power supply stability

### Debug Functions

```c
// Get raw joystick values for debugging
uint16_t x_raw, y_raw;
Joystick_GetRawValues(&x_raw, &y_raw);

// Test direction detection
Direction dir = Joystick_GetDirection();
```

## Optional Enhancements

### 1. **Button Support**
To add the joystick button (SW pin):
- Configure PA0, PA1, or PA2 as GPIO input with pull-up
- Add button handling in joystick.c
- Implement reset or pause functionality

### 2. **Analog Movement**
For variable speed movement:
- Use analog values instead of digital directions
- Implement acceleration based on displacement
- Add smooth tile animations

### 3. **Multi-directional Support**
For diagonal movements:
- Remove the "dominant axis" logic
- Support combined directions (e.g., DIR_UP_LEFT)
- Modify game logic for 8-direction movement

## Files Modified

- `Core/Src/main.c` - Added ADC initialization and joystick task
- `TouchGFX/gui/src/screen1_screen/Screen1View.cpp` - Updated include path
- All new files created as listed above

## Testing

1. **Compile the project**
2. **Flash to STM32F429I Discovery board**
3. **Connect joystick as per pin mapping**
4. **Test all four directions**
5. **Verify game responds correctly**

The joystick should now control the 2048 game with smooth, debounced input handling! 