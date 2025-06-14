# TouchGFX Designer Setup Guide - Clean 2048 UI

## Overview
This guide shows you how to set up a clean, modern 2048 game interface in TouchGFX Designer with all unnecessary boxes removed.

## Current Layout Design

### Screen Resolution: 240x320 (Portrait)

### Color Scheme
- Background: RGB(250, 248, 239) - Light beige
- Header/Game Board Background: RGB(187, 173, 160) - Medium brown
- Text: RGB(255, 255, 255) - White on headers, RGB(119, 110, 101) - Dark brown for body text

### UI Components Layout

#### 1. Background Box (backgroundBox)
- Position: (0, 0)
- Size: 240x320 (full screen)
- Color: RGB(250, 248, 239)
- Purpose: Main background

#### 2. Header Box (headerBox)
- Position: (10, 10)
- Size: 220x60
- Color: RGB(187, 173, 160)
- Purpose: Contains title and score

#### 3. Title Text (titleText)
- Position: (20, 20)
- Size: 100x40
- Text ID: T_2048_TITLE
- Content: "2048"
- Font: Title (24pt)
- Color: White

#### 4. Score Label (scoreText)
- Position: (130, 15)
- Size: 90x15
- Text ID: T_SCORE_LABEL
- Content: "SCORE"
- Font: Small (10pt)
- Color: White

#### 5. Score Value (scoreValue)
- Position: (130, 35)
- Size: 90x25
- Text ID: T_SCORE_VALUE
- Content: "0" (dynamic)
- Font: Large (18pt)
- Color: White

#### 6. Game Board Background (gameBoardBackground)
- Position: (20, 90)
- Size: 200x200
- Color: RGB(187, 173, 160)
- Purpose: Background for the 4x4 grid

#### 7. Game Board Container (gameBoardContainer)
- Position: (25, 95)
- Size: 190x190
- Purpose: Container for the GameBoardWidget

#### 8. Status Text (statusText)
- Position: (20, 300)
- Size: 200x15
- Text ID: T_STATUS
- Content: "Tilt to move tiles"
- Font: Small (10pt)
- Color: RGB(119, 110, 101)

## Steps to Set Up in TouchGFX Designer

### 1. Open TouchGFX Designer
```bash
cd d:\Workspace\DEV\IOT\2048-Remake\codebase\2048_Remake\TouchGFX
# Open 2048_Remake.touchgfx in TouchGFX Designer
```

### 2. Import Text Resources
1. In TouchGFX Designer, go to "Texts" tab
2. Import the text configuration from: `assets\texts\texts.json`
3. Or manually create these text entries:
   - T_2048_TITLE: "2048" (Title font)
   - T_SCORE_LABEL: "SCORE" (Small font)
   - T_SCORE_VALUE: "0" (Large font)
   - T_STATUS: "Tilt to move tiles" (Small font)
   - T_GAME_WON: "You Won!" (Medium font)
   - T_GAME_OVER: "Game Over!" (Medium font)
   - T_NEW_GAME: "Press button for new game" (Small font)

### 3. Set Up Fonts
Create these font groups:
- Title: 24pt
- Large: 18pt  
- Medium: 14pt
- Small: 10pt

### 4. Verify Layout
The TouchGFX project file should now show a clean layout with:
- No unnecessary boxes (box1-box7 removed)
- Proper header with title and score
- Centered game board area
- Status message at bottom

### 5. Connect GameBoardWidget
The GameBoardWidget will be added to the gameBoardContainer programmatically in Screen1View::setupGameBoard()

### 6. Generate Code
1. Click "Generate Code" in TouchGFX Designer
2. This will update the generated UI files

### 7. Build and Test
```bash
# In STM32CubeIDE or command line
make clean && make all
```

## UI Behavior

### Dynamic Elements
- Score updates in real-time during gameplay
- Status text changes based on game state:
  - Normal: "Tilt to move tiles"
  - Game Over: "Game Over! Press button for new game"
  - Game Won: "You Won! Press button for new game"

### Game Board
- 4x4 grid of tiles inside the game board container
- Each tile shows its value (2, 4, 8, 16, etc.)
- Empty tiles are shown with a darker background
- Tiles have different colors based on their value

## Color Values for Reference

### Main Colors
- Light Background: RGB(250, 248, 239) = #faf8ef
- Header/Board Background: RGB(187, 173, 160) = #bbada0
- Dark Text: RGB(119, 110, 101) = #776e65
- White Text: RGB(255, 255, 255) = #ffffff

### Tile Colors (for GameBoardWidget)
- Empty Tile: RGB(205, 193, 180) = #cdc1b4
- Tile 2: RGB(238, 228, 218) = #eee4da
- Tile 4: RGB(237, 224, 200) = #ede0c8
- Tile 8: RGB(242, 177, 121) = #f2b179
- And so on...

This creates a clean, professional 2048 game interface optimized for the STM32F429 240x320 display.
