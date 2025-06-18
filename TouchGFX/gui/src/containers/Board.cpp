#include <gui/containers/Board.hpp>
#include <bits/stdc++.h>
using namespace std;

int Board::board[4][4] = { 0 };
touchgfx::Unicode::UnicodeChar Board::textBuffers[16][10];

Board::Board() {
	Board::board[0][3] = 2;
	Board::board[0][1] = 2;
}

void Board::initialize() {
	BoardBase::initialize();
}

void Board::updateDisplay(int row, int col, int value) {
	touchgfx::Container *container = getContainer(row, col);
	touchgfx::TextAreaWithOneWildcard *textArea = getTextArea(row, col);

	if (value == 0) {
		container->setVisible(false);
	} else {
		container->setVisible(true);
		int index = row * 4 + col;
		touchgfx::Unicode::snprintf(textBuffers[index], 10, "%d", value);
		textArea->setWildcard(textBuffers[index]);
		textArea->invalidate();
	}
}

int Board::getValue(int row, int col) const {
	return Board::board[row][col];
}

void Board::addRandomTile() {
	vector<pair<int, int>> emptyCells;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Board::board[i][j] == 0) {
				emptyCells.push_back( { i, j });
			}
		}
	}

	if (!emptyCells.empty()) {
		int idx = rand() % emptyCells.size();
		int value = (rand() % 10 == 0) ? 4 : 2;
		Board::board[emptyCells[idx].first][emptyCells[idx].second] = value;
	}
}

bool Board::moveLeft() {
	bool moved = false;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 3; col++) {
			if (Board::board[row][col] == Board::board[row][col + 1]
					&& Board::board[row][col] != 0) {
				Board::board[row][col] *= 2;
				Board::board[row][col + 1] = 0;
				moved = true;
			}
		}

		for (int col = 0; col < 3; col++) {
			if (Board::board[row][col] == 0) {
				for (int k = col + 1; k < 4; k++) {
					if (Board::board[row][k] != 0) {
						Board::board[row][col] = Board::board[row][k];
						Board::board[row][k] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}
	return moved;
}

bool Board::moveRight() {
	bool moved = false;
	for (int row = 0; row < 4; row++) {
		for (int col = 3; col > 0; col--) {
			if (Board::board[row][col] == Board::board[row][col - 1]
					&& Board::board[row][col] != 0) {
				Board::board[row][col] *= 2;
				Board::board[row][col - 1] = 0;
				moved = true;
			}
		}

		for (int col = 3; col > 0; col--) {
			if (Board::board[row][col] == 0) {
				for (int k = col - 1; k >= 0; k--) {
					if (Board::board[row][k] != 0) {
						Board::board[row][col] = Board::board[row][k];
						Board::board[row][k] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}
	return moved;
}

bool Board::moveUp() {
	bool moved = false;
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 3; row++) {
			if (Board::board[row][col] == Board::board[row + 1][col]
					&& Board::board[row][col] != 0) {
				Board::board[row][col] *= 2;
				Board::board[row + 1][col] = 0;
				moved = true;
			}
		}

		for (int row = 0; row < 3; row++) {
			if (Board::board[row][col] == 0) {
				for (int k = row + 1; k < 4; k++) {
					if (Board::board[k][col] != 0) {
						Board::board[row][col] = Board::board[k][col];
						Board::board[k][col] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}
	return moved;
}

bool Board::moveDown() {
	bool moved = false;
	for (int col = 0; col < 4; col++) {
		for (int row = 3; row > 0; row--) {
			if (Board::board[row][col] == Board::board[row - 1][col]
					&& Board::board[row][col] != 0) {
				Board::board[row][col] *= 2;
				Board::board[row - 1][col] = 0;
				moved = true;
			}
		}

		for (int row = 3; row > 0; row--) {
			if (Board::board[row][col] == 0) {
				for (int k = row - 1; k >= 0; k--) {
					if (Board::board[k][col] != 0) {
						Board::board[row][col] = Board::board[k][col];
						Board::board[k][col] = 0;
						moved = true;
						break;
					}
				}
			}
		}
	}
	return moved;
}

bool Board::canMove() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Board::board[i][j] == 0)
				return true;
			if (i < 3 && Board::board[i][j] == Board::board[i + 1][j])
				return true;
			if (j < 3 && Board::board[i][j] == Board::board[i][j + 1])
				return true;
		}
	}
	return false;
}

int Board::getScore() {
	int score = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			score += Board::board[i][j];
		}
	}
	return score;
}

touchgfx::Container* Board::getContainer(int row, int col) {
	int index = row * 4 + col;
	switch (index) {
	case 0:
		return &container1;
	case 1:
		return &container1_2;
	case 2:
		return &container1_3;
	case 3:
		return &container1_4;
	case 4:
		return &container1_5;
	case 5:
		return &container1_6;
	case 6:
		return &container1_7;
	case 7:
		return &container1_8;
	case 8:
		return &container1_9;
	case 9:
		return &container1_10;
	case 10:
		return &container1_11;
	case 11:
		return &container1_12;
	case 12:
		return &container1_13;
	case 13:
		return &container1_14;
	case 14:
		return &container1_15;
	case 15:
		return &container1_16;
	default:
		return nullptr;
	}
}

touchgfx::TextAreaWithOneWildcard* Board::getTextArea(int row, int col) {
	int index = row * 4 + col;
	switch (index) {
	case 0:
		return &textArea1;
	case 1:
		return &textArea1_2;
	case 2:
		return &textArea1_3;
	case 3:
		return &textArea1_4;
	case 4:
		return &textArea1_5;
	case 5:
		return &textArea1_6;
	case 6:
		return &textArea1_7;
	case 7:
		return &textArea1_8;
	case 8:
		return &textArea1_9;
	case 9:
		return &textArea1_10;
	case 10:
		return &textArea1_11;
	case 11:
		return &textArea1_12;
	case 12:
		return &textArea1_13;
	case 13:
		return &textArea1_14;
	case 14:
		return &textArea1_15;
	case 15:
		return &textArea1_16;
	default:
		return nullptr;
	}
}
