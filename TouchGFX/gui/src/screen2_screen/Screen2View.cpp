#include <gui/screen2_screen/Screen2View.hpp>
#include "cmsis_os2.h"
#include "gui/common/Direction.hpp"
#include "main.h"  // For HAL_GetTick and UART functions
#include <cstdio>  // For snprintf
#include <stdint.h> // For uint32_t
#include <touchgfx/hal/HAL.hpp>  // For flushFrameBuffer
#include <texts/TextKeysAndLanguages.hpp> // For text IDs
#include <gui/containers/Board.hpp> // For Board class

touchgfx::Unicode::UnicodeChar Screen2View::scoreBuffer[10];
touchgfx::Unicode::UnicodeChar Screen2View::highestScoreBuffer[10];

Screen2View::Screen2View() : finalScore(0), highestScore(0), gameWon(false)
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
    
    // Get endgame data from application
    int score = application().getEndGameScore();
    bool won = application().getEndGameWon();
    int highest = application().getHighestScore();
    
    setFinalScore(score);
    setHighestScore(highest);
    setGameResult(won);
    
    #ifdef HAL_UART_MODULE_ENABLED
    extern UART_HandleTypeDef huart1;
    char msg[100];
    int len = snprintf(msg, sizeof(msg), "=== ENDGAME SCREEN: Setup completed, Score: %d, Highest: %d, Won: %s ===\r\n", 
                       score, highest, won ? "YES" : "NO");
    HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
    #endif
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::setFinalScore(int score)
{
    finalScore = score;
    touchgfx::Unicode::snprintf(scoreBuffer, 10, "%d", finalScore);
    endGameFrame1.setCurrentScore(scoreBuffer);
    
    #ifdef HAL_UART_MODULE_ENABLED
    extern UART_HandleTypeDef huart1;
    char msg[100];
    int len = snprintf(msg, sizeof(msg), "=== ENDGAME: Final score set to %d ===\r\n", finalScore);
    HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
    #endif
}

void Screen2View::setHighestScore(int score)
{
    highestScore = score;
    touchgfx::Unicode::snprintf(highestScoreBuffer, 10, "%d", highestScore);
    endGameFrame1.setHighestScore(highestScoreBuffer);
    
    #ifdef HAL_UART_MODULE_ENABLED
    extern UART_HandleTypeDef huart1;
    char msg[100];
    int len = snprintf(msg, sizeof(msg), "=== ENDGAME: Highest score set to %d ===\r\n", highestScore);
    HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
    #endif
}

void Screen2View::setGameResult(bool won)
{
    gameWon = won;
    
    // Update title text based on win/lose using the Designer elements
    if (gameWon) {
        // Set "You Won!" message
        touchgfx::Unicode::UnicodeChar winBuffer[20];
        touchgfx::Unicode::strncpy(winBuffer, (const touchgfx::Unicode::UnicodeChar*)L"You Won!", 20);
        endGameFrame1.setTitleMessage(winBuffer);
        
        #ifdef HAL_UART_MODULE_ENABLED
        extern UART_HandleTypeDef huart1;
        char msg[100];
        int len = snprintf(msg, sizeof(msg), "=== ENDGAME: Player WON! ===\r\n");
        HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
        #endif
    } else {
        // Set "Game Over" message
        touchgfx::Unicode::UnicodeChar loseBuffer[20];
        touchgfx::Unicode::strncpy(loseBuffer, (const touchgfx::Unicode::UnicodeChar*)L"Game Over", 20);
        endGameFrame1.setTitleMessage(loseBuffer);
        
        #ifdef HAL_UART_MODULE_ENABLED
        extern UART_HandleTypeDef huart1;
        char msg[100];
        int len = snprintf(msg, sizeof(msg), "=== ENDGAME: Game Over ===\r\n");
        HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
        #endif
    }
}

void Screen2View::handlePlayAgainButtonClicked()
{
    #ifdef HAL_UART_MODULE_ENABLED
    extern UART_HandleTypeDef huart1;
    char msg[100];
    int len = snprintf(msg, sizeof(msg), "=== ENDGAME: Play Again button clicked, resetting board ===\r\n");
    HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
    #endif
    
    // Reset the board state before transitioning back to game
    Board tempBoard;
    tempBoard.resetBoard();
    
    #ifdef HAL_UART_MODULE_ENABLED
    len = snprintf(msg, sizeof(msg), "=== ENDGAME: Board reset completed, transitioning to Screen1 ===\r\n");
    HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
    #endif
    
    // Transition back to Screen1 (game screen)
    application().gotoScreen1ScreenNoTransition();
}

void Screen2View::handleTickEvent()
{
    Screen2ViewBase::handleTickEvent();
}

extern osMessageQueueId_t directionQueueHandle;

void Screen2View::tickEvent()
{
    // Check for joystick input to restart game
    if (directionQueueHandle != NULL) {
        GameDirection dir;
        osStatus_t status = osMessageQueueGet(directionQueueHandle, &dir, NULL, 0);
        
        if (status == osOK) {
            // Any joystick input will restart the game
            #ifdef HAL_UART_MODULE_ENABLED
            extern UART_HandleTypeDef huart1;
            char msg[100];
            int len = snprintf(msg, sizeof(msg), "=== ENDGAME: Joystick input detected, restarting game ===\r\n");
            HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
            #endif
            
            handlePlayAgainButtonClicked();
        }
    }
} 