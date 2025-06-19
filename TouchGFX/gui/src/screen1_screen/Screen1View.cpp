#include <gui/screen1_screen/Screen1View.hpp>
#include "cmsis_os2.h"
#include "gui/common/Direction.hpp"
#include "main.h"  // For HAL_GetTick and UART functions
#include <cstdio>  // For snprintf
#include <touchgfx/hal/HAL.hpp>  // For flushFrameBuffer

Screen1View *Screen1View::instance = nullptr;

Screen1View::Screen1View() {
	instance = this;
}

Screen1View* getInstance() {
	return Screen1View::instance;
}

static void resetGameCallback() {
	if (getInstance()) {
		getInstance()->handleResetGame();
	}
}
void Screen1View::setupScreen() {
	Screen1ViewBase::setupScreen();
	
	#ifdef HAL_UART_MODULE_ENABLED
	extern UART_HandleTypeDef huart1;
	char msg[100];
	int len = snprintf(msg, sizeof(msg), "=== SETUP: Initial board state ===\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
	#endif
	
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			int value = board1.getValue(row, col);
			board1.updateDisplay(row, col, value);
			
			#ifdef HAL_UART_MODULE_ENABLED
			if (value != 0) {
				int len2 = snprintf(msg, sizeof(msg), "=== SETUP: board[%d][%d] = %d\r\n", row, col, value);
				HAL_UART_Transmit(&huart1, (uint8_t*)msg, len2, HAL_MAX_DELAY);
			}
			#endif
		}
	}
	mainFrame1.setScore(0);

	mainFrame1.setResetCallback(resetGameCallback);
}

void Screen1View::tearDownScreen() {
	Screen1ViewBase::tearDownScreen();
}

void Screen1View::handleJoystickUp() {
	#ifdef HAL_UART_MODULE_ENABLED
	extern UART_HandleTypeDef huart1;
	char msg[100];
	int len = snprintf(msg, sizeof(msg), "*** GAME: Processing UP move\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
	#endif
	
	if (board1.moveUp()) {
		#ifdef HAL_UART_MODULE_ENABLED
		int len2 = snprintf(msg, sizeof(msg), "*** GAME: UP move successful, updating display\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)msg, len2, HAL_MAX_DELAY);
		#endif
		
		board1.addRandomTile();
		
		// Update all tiles to reflect the new board state
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				int value = board1.getValue(row, col);
				board1.updateDisplay(row, col, value);
			}
		}
		
		// Update score and refresh display
		mainFrame1.setScore(board1.getScore());
		application().requestRedraw();
		invalidate();
		board1.invalidate();
		mainFrame1.invalidate();
		touchgfx::HAL::getInstance()->flushFrameBuffer();
		
		#ifdef HAL_UART_MODULE_ENABLED
		osDelay(10);
		int len3 = snprintf(msg, sizeof(msg), "*** DISPLAY: UP move completed\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)msg, len3, HAL_MAX_DELAY);
		#endif
	} else {
		#ifdef HAL_UART_MODULE_ENABLED
		int len2 = snprintf(msg, sizeof(msg), "*** GAME: UP move failed - no valid moves\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)msg, len2, HAL_MAX_DELAY);
		#endif
	}

	if (!board1.canMove()) {
		// Game over logic can be added here
	}
}

void Screen1View::handleJoystickDown() {
	#ifdef HAL_UART_MODULE_ENABLED
	extern UART_HandleTypeDef huart1;
	char msg[100];
	int len = snprintf(msg, sizeof(msg), "*** GAME: Processing DOWN move\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
	#endif
	
	if (board1.moveDown()) {
		#ifdef HAL_UART_MODULE_ENABLED
		int len2 = snprintf(msg, sizeof(msg), "*** GAME: DOWN move successful, updating display\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)msg, len2, HAL_MAX_DELAY);
		#endif
		
		board1.addRandomTile();
		
		// Update all tiles to reflect the new board state
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				int value = board1.getValue(row, col);
				board1.updateDisplay(row, col, value);
			}
		}
		
		// Update score and refresh display
		mainFrame1.setScore(board1.getScore());
		application().requestRedraw();
		invalidate();
		board1.invalidate();
		mainFrame1.invalidate();
		touchgfx::HAL::getInstance()->flushFrameBuffer();
		
		#ifdef HAL_UART_MODULE_ENABLED
		osDelay(10);
		int len3 = snprintf(msg, sizeof(msg), "*** DISPLAY: DOWN move completed\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)msg, len3, HAL_MAX_DELAY);
		#endif
	} else {
		#ifdef HAL_UART_MODULE_ENABLED
		int len2 = snprintf(msg, sizeof(msg), "*** GAME: DOWN move failed - no valid moves\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)msg, len2, HAL_MAX_DELAY);
		#endif
	}

	if (!board1.canMove()) {
		// Game over logic can be added here
	}
}

void Screen1View::handleJoystickLeft() {
	#ifdef HAL_UART_MODULE_ENABLED
	extern UART_HandleTypeDef huart1;
	char msg[100];
	int len = snprintf(msg, sizeof(msg), "*** GAME: Processing LEFT move\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
	#endif
	
	if (board1.moveLeft()) {
		#ifdef HAL_UART_MODULE_ENABLED
		int len2 = snprintf(msg, sizeof(msg), "*** GAME: LEFT move successful, updating display\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)msg, len2, HAL_MAX_DELAY);
		#endif
		
		board1.addRandomTile();
		
		// Update all tiles to reflect the new board state
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				int value = board1.getValue(row, col);
				board1.updateDisplay(row, col, value);
			}
		}
		
		// Update score and refresh display
		mainFrame1.setScore(board1.getScore());
		application().requestRedraw();
		invalidate();
		board1.invalidate();
		mainFrame1.invalidate();
		touchgfx::HAL::getInstance()->flushFrameBuffer();
		
		#ifdef HAL_UART_MODULE_ENABLED
		osDelay(10);
		int len3 = snprintf(msg, sizeof(msg), "*** DISPLAY: LEFT move completed\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)msg, len3, HAL_MAX_DELAY);
		#endif
	} else {
		#ifdef HAL_UART_MODULE_ENABLED
		int len2 = snprintf(msg, sizeof(msg), "*** GAME: LEFT move failed - no valid moves\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)msg, len2, HAL_MAX_DELAY);
		#endif
	}

	if (!board1.canMove()) {
		// Game over logic can be added here
	}
}

void Screen1View::handleJoystickRight() {
	#ifdef HAL_UART_MODULE_ENABLED
	extern UART_HandleTypeDef huart1;
	char msg[100];
	int len = snprintf(msg, sizeof(msg), "*** GAME: Processing RIGHT move\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
	#endif
	
	if (board1.moveRight()) {
		#ifdef HAL_UART_MODULE_ENABLED
		int len2 = snprintf(msg, sizeof(msg), "*** GAME: RIGHT move successful, updating display\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)msg, len2, HAL_MAX_DELAY);
		#endif
		
		board1.addRandomTile();
		
		// Update all tiles to reflect the new board state
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				int value = board1.getValue(row, col);
				board1.updateDisplay(row, col, value);
			}
		}
		
		// Update score and refresh display
		mainFrame1.setScore(board1.getScore());
		application().requestRedraw();
		invalidate();
		board1.invalidate();
		mainFrame1.invalidate();
		touchgfx::HAL::getInstance()->flushFrameBuffer();
		
		#ifdef HAL_UART_MODULE_ENABLED
		osDelay(10);
		int len3 = snprintf(msg, sizeof(msg), "*** DISPLAY: RIGHT move completed\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)msg, len3, HAL_MAX_DELAY);
		#endif
	} else {
		#ifdef HAL_UART_MODULE_ENABLED
		int len2 = snprintf(msg, sizeof(msg), "*** GAME: RIGHT move failed - no valid moves\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)msg, len2, HAL_MAX_DELAY);
		#endif
	}

	if (!board1.canMove()) {
		// Game over logic can be added here
	}
}

void Screen1View::handleResetGame() {
	mainFrame1.setScore(2048);
	board1.initialize();
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			int value = board1.getValue(row, col);
			board1.updateDisplay(row, col, value);
		}
	}
}

extern osMessageQueueId_t directionQueueHandle;

void Screen1View::handleTickEvent() {
	Screen1ViewBase::handleTickEvent();
}
void Screen1View::tickEvent()
{
    static int tickCounter = 0;
    static uint32_t lastDebugTime = 0;
    tickCounter++;

    // Debug: Show that tickEvent is being called
    uint32_t currentTime = HAL_GetTick();
    if ((currentTime - lastDebugTime) >= 2000) {  // Every 2 seconds
        #ifdef HAL_UART_MODULE_ENABLED
        extern UART_HandleTypeDef huart1;
        char msg[100];
        int len = snprintf(msg, sizeof(msg), "### GUI: tickEvent() running, counter=%d\r\n", tickCounter);
        HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
        
        // Check if queue handle is valid
        if (directionQueueHandle != NULL) {
            len = snprintf(msg, sizeof(msg), "### QUEUE: Handle is valid, checking messages...\r\n");
            HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
        } else {
            len = snprintf(msg, sizeof(msg), "### QUEUE: Handle is NULL!\r\n");
            HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
        }
        #endif
        lastDebugTime = currentTime;
    }

    // Check message queue every tick for maximum responsiveness
    if (directionQueueHandle != NULL) {
        GameDirection dir;
        osStatus_t status = osMessageQueueGet(directionQueueHandle, &dir, NULL, 0);
        
        if (status == osOK) {
            // Direction received from joystick - add debug output
            #ifdef HAL_UART_MODULE_ENABLED
            extern UART_HandleTypeDef huart1;
            const char* dirNames[] = {"NONE", "LEFT", "RIGHT", "UP", "DOWN"};
            const char* dirName = (dir <= 4) ? dirNames[dir] : "UNKNOWN";
            char msg[64];
            int len = snprintf(msg, sizeof(msg), "<<< GUI: Received %s, processing...\r\n", dirName);
            HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
            #endif
            
            switch (dir) {
                case DIR_LEFT:   handleJoystickLeft(); break;
                case DIR_RIGHT:  handleJoystickRight(); break;
                case DIR_UP:     handleJoystickUp(); break;
                case DIR_DOWN:   handleJoystickDown(); break;
                default: break;
            }
        }
    }
}
