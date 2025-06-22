#include <gui/containers/Board.hpp>

int Board::board[4][4] = { 0 };
touchgfx::Unicode::UnicodeChar Board::textBuffers[16][10];
bool Board::gameWon = false;

Board::Board() {
	// Initialize with tiles that can actually move
	Board::board[1][1] = 2;  // Middle position - can move in all directions
	Board::board[2][2] = 2;  // Another middle position
	Board::gameWon = false;
}

void Board::initialize() {
	BoardBase::initialize();
}

void Board::updateDisplay(int row, int col, int value) {
	touchgfx::Container *container = getContainer(row, col);
	touchgfx::TextAreaWithOneWildcard *textArea = getTextArea(row, col);

	#ifdef HAL_UART_MODULE_ENABLED
	extern UART_HandleTypeDef huart1;
	char msg[100];
	if (value != 0) {  // Only log non-zero tiles to reduce output
		int len = snprintf(msg, sizeof(msg), "### TILE: [%d][%d]=%d\r\n", row, col, value);
		HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
	}
	#endif

	if (value == 0) {
		container->setVisible(false);
		container->invalidate();  // Invalidate when hiding
	} else {
		container->setVisible(true);
		int index = row * 4 + col;
		touchgfx::Unicode::snprintf(textBuffers[index], 10, "%d", value);
		textArea->setWildcard(textBuffers[index]);
		
		// Force multiple invalidations
		textArea->invalidateContent();
		textArea->invalidate();
		container->invalidate();
	}
}

int Board::getValue(int row, int col) const {
	return Board::board[row][col];
}

void Board::addRandomTile() {
	// Find all empty cells using simple arrays (no STL!)
	int emptyRows[16];    // Max 16 empty cells in 4x4 grid
	int emptyCols[16];
	int emptyCount = 0;
	
	// Collect all empty positions
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Board::board[i][j] == 0) {
				emptyRows[emptyCount] = i;
				emptyCols[emptyCount] = j;
				emptyCount++;
			}
		}
	}
	
	// If no empty cells, return
	if (emptyCount == 0) {
		return;
	}
	
	// Simple pseudo-random selection using a static counter
	static int randomCounter = 0;
	randomCounter += 7;  // Prime number for better distribution
	int selectedIndex = randomCounter % emptyCount;
	
	int row = emptyRows[selectedIndex];
	int col = emptyCols[selectedIndex];
	
	// Simple pseudo-random value: mostly 2s, occasionally 4s
	int value = ((randomCounter % 10) < 9) ? 2 : 4;
	
	Board::board[row][col] = value;
	
	#ifdef HAL_UART_MODULE_ENABLED
	extern UART_HandleTypeDef huart1;
	char msg[100];
	int len = snprintf(msg, sizeof(msg), "*** RANDOM: Added %d at [%d][%d] (from %d empty)\r\n", 
	                   value, row, col, emptyCount);
	HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
	#endif
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
				
				// Check if we reached 2048
				if (Board::board[row][col] == 2048) {
					gameWon = true;
				}
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
				
				// Check if we reached 2048
				if (Board::board[row][col] == 2048) {
					gameWon = true;
				}
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
				
				// Check if we reached 2048
				if (Board::board[row][col] == 2048) {
					gameWon = true;
				}
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
				
				// Check if we reached 2048
				if (Board::board[row][col] == 2048) {
					gameWon = true;
				}
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

bool Board::canMove() const {
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

// Endgame detection methods
bool Board::hasWon() const {
	if (gameWon) return true;
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Board::board[i][j] == 2048) {
				return true;
			}
		}
	}
	return false;
}

bool Board::hasLost() const {
	// Game is lost if board is full and no moves are possible
	return !canMove();
}

bool Board::isGameOver() const {
	return hasWon() || hasLost();
}

void Board::resetBoard() {
	// Clear the board
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Board::board[i][j] = 0;
		}
	}
	
	// Reset game won flag
	gameWon = false;
	
	// Add initial tiles
	Board::board[1][1] = 2;
	Board::board[2][2] = 2;
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

