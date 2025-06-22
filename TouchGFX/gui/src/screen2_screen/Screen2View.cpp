#include <gui/screen2_screen/Screen2View.hpp>
#include "cmsis_os2.h"
#include "gui/common/Direction.hpp"
#include "main.h"  // For HAL_GetTick and UART functions
#include <cstdio>  // For snprintf
#include <stdint.h> // For uint32_t
#include <touchgfx/hal/HAL.hpp>  // For flushFrameBuffer
#include <texts/TextKeysAndLanguages.hpp> // For text IDs

touchgfx::Unicode::UnicodeChar Screen2View::scoreBuffer[10];

Screen2View::Screen2View() : finalScore(0), gameWon(false)
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
    
    // Get endgame data from application
    int score = application().getEndGameScore();
    bool won = application().getEndGameWon();
    
    setFinalScore(score);
    setGameResult(won);
    
    #ifdef HAL_UART_MODULE_ENABLED
    extern UART_HandleTypeDef huart1;
    char msg[100];
    int len = snprintf(msg, sizeof(msg), "=== ENDGAME SCREEN: Setup completed, Score: %d, Won: %s ===\r\n", 
                       score, won ? "YES" : "NO");
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
    scoreValue.setWildcard(scoreBuffer);
    scoreValue.invalidate();
    
    #ifdef HAL_UART_MODULE_ENABLED
    extern UART_HandleTypeDef huart1;
    char msg[100];
    int len = snprintf(msg, sizeof(msg), "=== ENDGAME: Final score set to %d ===\r\n", finalScore);
    HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
    #endif
}

void Screen2View::setGameResult(bool won)
{
    gameWon = won;
    
    // Update title text based on win/lose
    if (gameWon) {
        // Use "Replay" text for won condition
        titleText.setTypedText(touchgfx::TypedText(T___SINGLEUSE_HZSS)); // "Replay"
        #ifdef HAL_UART_MODULE_ENABLED
        extern UART_HandleTypeDef huart1;
        char msg[100];
        int len = snprintf(msg, sizeof(msg), "=== ENDGAME: Player WON! ===\r\n");
        HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
        #endif
    } else {
        // Use "Exit" text for game over condition
        titleText.setTypedText(touchgfx::TypedText(T___SINGLEUSE_K26Y)); // "Exit"
        #ifdef HAL_UART_MODULE_ENABLED
        extern UART_HandleTypeDef huart1;
        char msg[100];
        int len = snprintf(msg, sizeof(msg), "=== ENDGAME: Game Over ===\r\n");
        HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
        #endif
    }
    
    titleText.invalidate();
}

void Screen2View::handlePlayAgainButtonClicked()
{
    #ifdef HAL_UART_MODULE_ENABLED
    extern UART_HandleTypeDef huart1;
    char msg[100];
    int len = snprintf(msg, sizeof(msg), "=== ENDGAME: Play Again button clicked ===\r\n");
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