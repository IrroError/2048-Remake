#include <gui/screen1_screen/Screen1View.hpp>
#include "cmsis_os2.h"
#include "Direction.h"

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
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			int value = board1.getValue(row, col);
			board1.updateDisplay(row, col, value);
		}
	}
	mainFrame1.setScore(0);

	mainFrame1.setResetCallback(resetGameCallback);
}

void Screen1View::tearDownScreen() {
	Screen1ViewBase::tearDownScreen();
}

void Screen1View::handleJoystickUp() {
	if (board1.moveUp()) {
		board1.randomTile();
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				int value = board1.getValue(row, col);
				board1.updateDisplay(row, col, value);
			}
		}
		mainFrame1.setScore(board1.getScore());
	}

	if (!board1.canMove()) {
		//
	}
}

void Screen1View::handleJoystickDown() {
	if (board1.moveDown()) {
		board1.randomTile();
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				int value = board1.getValue(row, col);
				board1.updateDisplay(row, col, value);
			}
		}
		mainFrame1.setScore(board1.getScore());
	}

	if (!board1.canMove()) {
		//
	}
}

void Screen1View::handleJoystickLeft() {
	if (board1.moveLeft()) {
		board1.randomTile();
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				int value = board1.getValue(row, col);
				board1.updateDisplay(row, col, value);
			}
		}
		mainFrame1.setScore(board1.getScore());
	}

	if (!board1.canMove()) {
		//
	}
}

void Screen1View::handleJoystickRight() {
	if (board1.moveRight()) {
		board1.randomTile();
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				int value = board1.getValue(row, col);
				board1.updateDisplay(row, col, value);
			}
		}
		mainFrame1.setScore(board1.getScore());
	}

	if (!board1.canMove()) {
		//
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
    tickCounter++;

    if (tickCounter % 3 == 0) {
        ::Direction dir = DIR_RIGHT;
        if (osMessageQueueGet(directionQueueHandle, &dir, NULL, 0) == osOK) {
            switch (dir) {
                case DIR_LEFT:   handleJoystickLeft(); break;
                case DIR_RIGHT:  handleJoystickRight(); break;
                case DIR_UP:     handleJoystickUp(); break;
                case DIR_DOWN:   handleJoystickDown(); break;
                default: break;
            }
        }
        tickCounter = 0;
    }
}
