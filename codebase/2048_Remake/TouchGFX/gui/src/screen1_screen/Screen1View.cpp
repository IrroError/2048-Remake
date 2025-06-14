#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/Unicode.hpp>
#include <GameBoard.hpp>

Screen1View::Screen1View()
{
    // Constructor - UI elements are created by TouchGFX Designer
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    setupGameBoard();
    initializeTextValues();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::setupGameBoard()
{
    // Position the game board widget over the gameBoardContainer area
    // The gameBoardContainer is a Box at (25, 82) with size (190, 190)
    // We'll position our game board widget at the same location
    gameBoardWidget.setPosition(25, 82, 190, 190);
    add(gameBoardWidget);
}

void Screen1View::initializeTextValues()
{
    // Initialize score display
    Unicode::snprintf(scoreBuffer, 10, "0");
    
    // Update the score value text
    T_SCORE_VALUE.invalidate();
    
    // Add some test tiles to see the visual result
    // This is temporary - remove this once full game integration is complete
    testGameBoard();
}

void Screen1View::testGameBoard()
{
    // Create a test GameBoard instance with some tiles for visual testing
    // This demonstrates the tile colors and layout
    GameBoard testBoard;
    
    // Add some test tiles to see different colors
    testBoard.setTile(0, 0, 2);    // Light beige
    testBoard.setTile(0, 1, 4);    // Light yellow
    testBoard.setTile(1, 0, 8);    // Orange
    testBoard.setTile(1, 1, 16);   // Darker orange
    testBoard.setTile(2, 0, 32);   // Red-orange
    testBoard.setTile(2, 1, 64);   // Red
    testBoard.setTile(3, 0, 128);  // Yellow
    testBoard.setTile(3, 1, 256);  // Golden
    
    // Update the visual game board
    gameBoardWidget.updateFromGameBoard(testBoard);
}

void Screen1View::updateGameBoard(const GameBoard& gameBoard)
{
    gameBoardWidget.updateFromGameBoard(gameBoard);
}

void Screen1View::updateScore(uint32_t score)
{
    Unicode::snprintf(scoreBuffer, 10, "%lu", score);
    // Note: For dynamic text updates, you may need to use setWildcard if the text resource supports it
    // For now, just invalidate to trigger a redraw
    T_SCORE_VALUE.invalidate();
}

void Screen1View::showGameOver()
{
    setStatusMessage("Game Over! Press button for new game");
}

void Screen1View::showGameWon()
{
    setStatusMessage("You Won! Press button for new game");
}

void Screen1View::hideGameOverWon()
{
    setStatusMessage("Tilt to move tiles");
}

void Screen1View::setStatusMessage(const char* message)
{
    // The T_STATUS TextArea is now generated and available
    // Note: For dynamic text updates, you might need to create text resources with wildcards
    // For now, just invalidate to trigger a redraw with the existing text
    T_STATUS.invalidate();
}
