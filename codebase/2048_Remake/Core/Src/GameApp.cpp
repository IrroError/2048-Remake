#include "GameApp.hpp"
#include "DebugUART.hpp"
#include "cmsis_os.h"

#ifdef __cplusplus
#include <ctime>
#else
#include <time.h>
#endif

// Forward declaration
#include "gui/screen1_screen/Screen1Presenter.hpp"

// Global instance
static GameApp* g_gameApp = nullptr;

// External SPI handle (defined in main.c)
extern SPI_HandleTypeDef hspi5;
extern UART_HandleTypeDef huart1;

GameApp::GameApp() 
    : gyroscope(nullptr), uiPresenter(nullptr), isGameRunning(false), 
      gameWon(false), gameOver(false), lastInputTime(0) {
}

void GameApp::initialize() {
    // Initialize debug UART
    DebugUART::initialize(&huart1);
    DebugUART::print("=== 2048 Game Starting ===\r\n");
    
    // Initialize random seed
    srand(HAL_GetTick());
    
    // Initialize hardware
    initializeHardware();
    initializeGyroscope();
    
    // Start a new game
    gameBoard.resetGame();
    isGameRunning = true;
    gameWon = false;
    gameOver = false;
    
    DebugUART::print("Game initialized successfully\r\n");
    DebugUART::printBoard(gameBoard);
    
    // Update UI for initial state
    updateUI();
}

void GameApp::initializeHardware() {
    // Additional hardware initialization if needed
    // The basic peripherals are already initialized in main()
}

void GameApp::initializeGyroscope() {
    // Create gyroscope instance with SPI5 and CS pin PC1
    gyroscope = new Gyroscope(&hspi5, GPIOC, GPIO_PIN_1);
    
    if (!gyroscope->initialize()) {
        // Handle initialization error
        DebugUART::print("ERROR: Gyroscope initialization failed!\r\n");
        delete gyroscope;
        gyroscope = nullptr;
    } else {
        DebugUART::print("Gyroscope initialized successfully\r\n");
        // Set movement threshold (adjust as needed)
        gyroscope->setThresholds(1500);
    }
}

void GameApp::run() {
    while (1) {
        update();
        osDelay(50); // 20Hz update rate
    }
}

void GameApp::update() {
    if (!isGameRunning) {
        return;
    }
    
    // Handle tilt input from gyroscope
    handleTiltInput();
    
    // Update game state
    updateGameState();
    
    // Update UI
    updateUI();
}

void GameApp::handleTiltInput() {
    if (!gyroscope) {
        return;
    }
    
    // Check for input debouncing
    uint32_t currentTime = HAL_GetTick();
    if (currentTime - lastInputTime < INPUT_DEBOUNCE_MS) {
        return;
    }
      GameDirection tiltDirection = gyroscope->getTiltDirection();
    
    if (tiltDirection != GameDirection::NONE) {
        const char* dirStr = "UNKNOWN";
        switch(tiltDirection) {
            case GameDirection::UP: dirStr = "UP"; break;
            case GameDirection::DOWN: dirStr = "DOWN"; break;
            case GameDirection::LEFT: dirStr = "LEFT"; break;
            case GameDirection::RIGHT: dirStr = "RIGHT"; break;
            default: break;
        }
        
        DebugUART::printf("Tilt detected: %s\r\n", dirStr);
        
        bool moved = gameBoard.move(tiltDirection);
        
        if (moved) {
            lastInputTime = currentTime;
            DebugUART::print("Move successful!\r\n");
            DebugUART::printBoard(gameBoard);
            updateGameState();
        } else {
            DebugUART::print("No tiles moved\r\n");
        }
    }
}

void GameApp::handleUserButtonPress() {
    // Reset the game
    DebugUART::print("Button pressed - Resetting game\r\n");
    resetGame();
}

void GameApp::resetGame() {
    gameBoard.resetGame();
    isGameRunning = true;
    gameWon = false;
    gameOver = false;
    lastInputTime = 0;
    updateUI();
}

void GameApp::updateGameState() {
    // Check win condition
    if (!gameWon && gameBoard.hasWon()) {
        gameWon = true;
        // You could show a "You Win!" message here
        // But let the player continue playing
    }
    
    // Check game over condition
    if (gameBoard.isGameOver()) {
        gameOver = true;
        isGameRunning = false;
        // Show game over screen
    }
}

void GameApp::updateUI() {
    if (uiPresenter != nullptr) {
        uiPresenter->updateGameDisplay(gameBoard);
        
        if (gameWon && !gameOver) {
            uiPresenter->showGameWon();
        } else if (gameOver) {
            uiPresenter->showGameOver();
        } else {
            uiPresenter->hideGameOverWon();
        }
    }
}

void GameApp::setPresenter(Screen1Presenter* presenter) {
    uiPresenter = presenter;
    // Update UI immediately if game is already initialized
    if (isGameRunning) {
        updateUI();
    }
}

// C interface implementations
void gameApp_initialize(void) {
    if (g_gameApp == nullptr) {
        g_gameApp = new GameApp();
    }
    g_gameApp->initialize();
}

void gameApp_run(void) {
    if (g_gameApp != nullptr) {
        g_gameApp->run();
    }
}

void gameApp_handleButtonPress(void) {
    if (g_gameApp != nullptr) {
        g_gameApp->handleUserButtonPress();
    }
}

void gameApp_setPresenter(void* presenter) {
    if (g_gameApp != nullptr && presenter != nullptr) {
        g_gameApp->setPresenter(static_cast<Screen1Presenter*>(presenter));
    }
}
