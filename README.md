# 🎮 2048 Game - STM32F429I-DISC1 Implementation

A complete implementation of the classic 2048 puzzle game for the STM32F429I-DISC1 development board, featuring TouchGFX GUI, joystick controls, and comprehensive endgame functionality.

## 👥 Team Members

| Name | Student ID | Role |
|------|------------|------|
| **Dinh Ngoc Cam** | 20226016 | **Team Leader** |
| **Nguyen Ha Tam** | 20215241 | Developer |
| **Nguyen Huu Dat** | 20215192 | Developer |

## 🎯 Project Overview

This project implements a fully functional 2048 game on the STM32F429I-DISC1 board with:
- **TouchGFX GUI** with smooth animations and modern interface
- **ADC-based joystick input** for game controls
- **Complete endgame system** with win/lose detection
- **Score tracking** and display
- **FreeRTOS integration** for real-time performance

## ✨ Features

### 🎮 Game Mechanics
- **Classic 2048 gameplay** - Combine tiles to reach 2048
- **Smooth tile movements** in all 4 directions (Up, Down, Left, Right)
- **Proper tile spawning** - 90% chance for 2, 10% chance for 4
- **Score calculation** based on tile combinations
- **Win condition** - Reach the 2048 tile
- **Lose condition** - No more possible moves

### 🕹️ Controls
- **Joystick Input** - Use the onboard joystick for tile movement
- **ADC-based detection** with configurable thresholds
- **Debouncing** for reliable input handling
- **FreeRTOS queue** for responsive controls

### 🖥️ User Interface
- **320x240 TouchGFX display** optimized for STM32F429I-DISC1
- **Game board** with animated tile movements
- **Real-time score display**
- **Endgame screen** with final score and restart option
- **Clean, modern design** with proper color schemes

### 🏁 Endgame System
- **Automatic win/lose detection**
- **Dedicated endgame screen** (Screen2)
- **Final score display**
- **Restart functionality** via joystick input
- **Proper screen transitions**

## 🛠️ Technical Specifications

### Hardware Requirements
- **STM32F429I-DISC1** development board
- **Built-in LCD display** (320x240, 16bpp)
- **Built-in joystick** for input controls
- **ST-LINK debugger** (integrated)

### Software Stack
- **STM32CubeIDE** - Primary development environment
- **TouchGFX** - GUI framework and graphics
- **FreeRTOS** - Real-time operating system
- **STM32 HAL** - Hardware abstraction layer
- **ADC drivers** - For joystick input processing

### Performance Features
- **Real-time rendering** with TouchGFX optimization
- **Efficient memory usage** for embedded constraints
- **Smooth animations** at 60 FPS target
- **Low-latency input** response via FreeRTOS queues

## 🚀 Getting Started

### Prerequisites
1. **STM32CubeIDE** (latest version)
2. **TouchGFX Designer** (optional, for UI modifications)
3. **STM32CubeProgrammer** for flashing
4. **STM32F429I-DISC1** board with USB cable
5. **Hercules UART Terminal** (recommended for debugging)

### Build Instructions
1. **Clone the repository**:
   ```bash
   git clone https://github.com/IrroError/2048-Remake.git
   cd 2048-Remake
   ```

2. **Open in STM32CubeIDE** (choose one method):
   
   **Method A - Import Project:**
   - File → Import → Existing Projects into Workspace
   - Select the project root directory
   - Import the project
   
   **Method B - Direct Open:**
   - Navigate to the `STM32CubeIDE/` folder
   - Double-click on `.project` file
   - STM32CubeIDE will automatically open the project

3. **Build the project**:
   - Right-click project → Build Project
   - Or use Ctrl+B

4. **Flash to board**:
   - Connect STM32F429I-DISC1 via USB
   - Right-click project → Run As → STM32 C/C++ Application
   - Or use F11 for debug mode

### Alternative IDEs
The project supports multiple IDEs:
- **STM32CubeIDE** (recommended)
- **IAR EWARM** (version 8.50.9+)
- **Keil MDK-ARM**

To switch IDEs: Open `STM32F429I_DISCO_REV_D01.ioc` with STM32CubeMX and select your preferred IDE.

## 🎮 How to Play

1. **Power on** the STM32F429I-DISC1 board
2. **Use the joystick** to move tiles:
   - **Up** - Move tiles up
   - **Down** - Move tiles down  
   - **Left** - Move tiles left
   - **Right** - Move tiles right
3. **Combine tiles** with the same number to create larger numbers
4. **Reach 2048** to win the game
5. **Game over** when no more moves are possible
6. **Restart** by pressing any joystick direction on the endgame screen

## 📁 Project Structure

```
2048-Remake/
├── Core/                          # STM32 core files
│   ├── Inc/                       # Header files
│   └── Src/                       # Source files (main.c, etc.)
├── TouchGFX/                      # TouchGFX GUI implementation
│   ├── gui/                       # Custom GUI code
│   │   ├── include/gui/containers/# Board and MainFrame classes
│   │   ├── include/gui/screen1_screen/ # Game screen
│   │   ├── include/gui/screen2_screen/ # Endgame screen
│   │   └── src/                   # Implementation files
│   ├── generated/                 # Auto-generated TouchGFX files
│   └── assets/                    # Fonts, images, texts
├── Drivers/                       # STM32 HAL drivers
├── Middlewares/                   # FreeRTOS and TouchGFX framework
├── STM32CubeIDE/                  # IDE project files
└── README.md                      # This file
```

## 🔧 Development Notes

### 🖥️ Hercules UART Terminal Setup
**Hercules** has been tremendously helpful in the debugging process. To set it up:

1. **Download Hercules** from HW-group website
2. **Configure Serial Settings**:
   - **Port**: Select your STM32 COM port (usually COM3 or higher)
   - **Baud Rate**: `115200`
   - **Data Size**: `8 bits`
   - **Parity**: `None`
   - **Stop Bits**: `1`
   - **Flow Control**: `None`
3. **Connect** and monitor real-time debug output from the STM32 board
4. **Features used**:
   - Game state monitoring
   - Joystick input debugging
   - Score calculation verification
   - Endgame condition tracking

### Performance Monitoring
GPIO pins for performance testing:
- **VSYNC_FREQ** - Pin PE2
- **RENDER_TIME** - Pin PE3  
- **FRAME_RATE** - Pin PE4
- **MCU_ACTIVE** - Pin PE5

### Configuration
- **Display**: 320x240 pixels, 16bpp
- **TouchGFX**: Optimized for STM32F429I-DISC1
- **FreeRTOS**: Real-time task scheduling
- **ADC**: Joystick input processing

## 🐛 Troubleshooting

### Common Issues
1. **Build errors**: Ensure all paths are correctly set in STM32CubeIDE
2. **Flash errors**: Check STM32CubeProgrammer installation
3. **Display issues**: Verify TouchGFX configuration matches hardware
4. **Input not working**: Check joystick ADC configuration

### Debug Features
- **UART output** for debugging (if enabled)
- **STM32CubeIDE debugger** support
- **TouchGFX performance metrics**

## 📜 License

This project is developed for educational purposes as part of embedded systems coursework.

## 🙏 Acknowledgments

- **STMicroelectronics** for STM32F429I-DISC1 platform and development tools
- **TouchGFX team** for the excellent GUI framework
- **FreeRTOS** for real-time operating system capabilities
- **HW-group** for Hercules UART Terminal - invaluable for debugging and development
- **Course instructors** for guidance and support

---

**🎯 Ready to play 2048 on embedded hardware!** 🚀
 