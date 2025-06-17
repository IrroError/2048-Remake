#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View() {

}

void Screen1View::setupScreen() {
	Screen1ViewBase::setupScreen();
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			int value = board1.getValue(row, col);
			board1.updateDisplay(row, col, value);
		}
	}
	mainFrame1.setScore(2048);
}

void Screen1View::tearDownScreen() {
	Screen1ViewBase::tearDownScreen();
}
