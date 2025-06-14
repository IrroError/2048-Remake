#ifndef GAME_APP_HPP
#define GAME_APP_HPP

#include "main.h"
#include "GameBoard.hpp"
#include "Gyroscope.hpp"

// Forward declaration for TouchGFX
class Screen1Presenter;

class GameApp {
public:
    GameApp();
    ~GameApp() = default;
    
    // Main application methods
    void initialize();
    void run();
    void update();
    void resetGame();
    
    // Event handlers
    void handleUserButtonPress();
    void handleTiltInput();
    
    // UI Interface
    void setPresenter(Screen1Presenter* presenter);
    void updateUI();

private:
    GameBoard gameBoard;
    Gyroscope* gyroscope;
    Screen1Presenter* uiPresenter;
    bool isGameRunning;
    bool gameWon;
    bool gameOver;
    
    // Timing for input debouncing
    uint32_t lastInputTime;
    static const uint32_t INPUT_DEBOUNCE_MS = 300;
    
    // Initialize hardware
    void initializeHardware();
    void initializeGyroscope();
    
    // Game state management
    void updateGameState();
};

// C interface for integration with main.c
#ifdef __cplusplus
extern "C" {
#endif

void gameApp_initialize(void);
void gameApp_run(void);
void gameApp_handleButtonPress(void);
void gameApp_setPresenter(void* presenter); // void* to avoid C++ in C

#ifdef __cplusplus
}
#endif

#endif // GAME_APP_HPP
