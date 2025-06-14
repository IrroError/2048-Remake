#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <gui/common/GameBoardWidget.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    
    // Game UI update methods
    void updateGameBoard(const GameBoard& gameBoard);
    void updateScore(uint32_t score);
    void showGameOver();
    void showGameWon();
    void hideGameOverWon();
    void setStatusMessage(const char* message);

protected:
    // Game board widget for the 4x4 grid
    GameBoardWidget gameBoardWidget;
    
    // Score value buffer for text display
    Unicode::UnicodeChar scoreBuffer[10];
    
    // Layout constants
    static const int16_t SCREEN_WIDTH = 240; 
    static const int16_t SCREEN_HEIGHT = 320;
    
private:
    void setupGameBoard();
    void initializeTextValues();
    void testGameBoard(); // Temporary method for testing tile display
};

#endif // SCREEN1VIEW_HPP
