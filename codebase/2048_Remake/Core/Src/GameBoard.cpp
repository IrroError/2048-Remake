#include "GameBoard.hpp"

#ifdef __cplusplus
#include <cstring>
#else
#include <string.h>
#endif

GameBoard::GameBoard() : score(0), hasWon2048(false) {
    resetGame();
}

void GameBoard::resetGame() {
    // Clear the board
    memset(board, 0, sizeof(board));
    score = 0;
    hasWon2048 = false;
    
    // Add two initial tiles
    spawnNewTile();
    spawnNewTile();
}

bool GameBoard::spawnNewTile() {
    uint8_t emptyCount = getEmptyTileCount();
    if (emptyCount == 0) {
        return false; // Board is full
    }
    
    // Find a random empty position
    uint8_t targetEmpty = rand() % emptyCount;
    uint8_t currentEmpty = 0;
    
    for (uint8_t row = 0; row < BOARD_SIZE; row++) {
        for (uint8_t col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == 0) {
                if (currentEmpty == targetEmpty) {
                    // 90% chance for 2, 10% chance for 4
                    board[row][col] = (rand() % 10 == 0) ? 4 : 2;
                    return true;
                }
                currentEmpty++;
            }
        }
    }
    return false;
}

bool GameBoard::moveUp() {
    bool moved = false;
    
    for (uint8_t col = 0; col < BOARD_SIZE; col++) {
        uint16_t column[BOARD_SIZE];
        
        // Extract column
        for (uint8_t row = 0; row < BOARD_SIZE; row++) {
            column[row] = board[row][col];
        }
        
        // Slide and merge
        bool columnMoved = slideAndMergeRow(column);
        if (columnMoved) {
            moved = true;
        }
        
        // Put column back
        for (uint8_t row = 0; row < BOARD_SIZE; row++) {
            board[row][col] = column[row];
        }
    }
    
    if (moved) {
        spawnNewTile();
    }
    
    return moved;
}

bool GameBoard::moveDown() {
    bool moved = false;
    
    for (uint8_t col = 0; col < BOARD_SIZE; col++) {
        uint16_t column[BOARD_SIZE];
        
        // Extract column (reversed)
        for (uint8_t row = 0; row < BOARD_SIZE; row++) {
            column[row] = board[BOARD_SIZE - 1 - row][col];
        }
        
        // Slide and merge
        bool columnMoved = slideAndMergeRow(column);
        if (columnMoved) {
            moved = true;
        }
        
        // Put column back (reversed)
        for (uint8_t row = 0; row < BOARD_SIZE; row++) {
            board[BOARD_SIZE - 1 - row][col] = column[row];
        }
    }
    
    if (moved) {
        spawnNewTile();
    }
    
    return moved;
}

bool GameBoard::moveLeft() {
    bool moved = false;
    
    for (uint8_t row = 0; row < BOARD_SIZE; row++) {
        bool rowMoved = slideAndMergeRow(board[row]);
        if (rowMoved) {
            moved = true;
        }
    }
    
    if (moved) {
        spawnNewTile();
    }
    
    return moved;
}

bool GameBoard::moveRight() {
    bool moved = false;
    
    for (uint8_t row = 0; row < BOARD_SIZE; row++) {
        uint16_t rowReversed[BOARD_SIZE];
        
        // Reverse the row
        for (uint8_t col = 0; col < BOARD_SIZE; col++) {
            rowReversed[col] = board[row][BOARD_SIZE - 1 - col];
        }
        
        // Slide and merge
        bool rowMoved = slideAndMergeRow(rowReversed);
        if (rowMoved) {
            moved = true;
        }
        
        // Put row back (reversed)
        for (uint8_t col = 0; col < BOARD_SIZE; col++) {
            board[row][BOARD_SIZE - 1 - col] = rowReversed[col];
        }
    }
    
    if (moved) {
        spawnNewTile();
    }
    
    return moved;
}

bool GameBoard::move(GameDirection direction) {
    switch (direction) {
        case GameDirection::UP:
            return moveUp();
        case GameDirection::DOWN:
            return moveDown();
        case GameDirection::LEFT:
            return moveLeft();
        case GameDirection::RIGHT:
            return moveRight();
        default:
            return false;
    }
}

bool GameBoard::slideAndMergeRow(uint16_t row[BOARD_SIZE]) {
    bool moved = false;
    uint16_t newRow[BOARD_SIZE] = {0};
    uint8_t writePos = 0;
    
    // First pass: slide all non-zero tiles to the left
    for (uint8_t i = 0; i < BOARD_SIZE; i++) {
        if (row[i] != 0) {
            newRow[writePos] = row[i];
            if (writePos != i) {
                moved = true;
            }
            writePos++;
        }
    }
    
    // Second pass: merge adjacent equal tiles
    for (uint8_t i = 0; i < BOARD_SIZE - 1; i++) {
        if (newRow[i] != 0 && newRow[i] == newRow[i + 1]) {
            newRow[i] *= 2;
            score += newRow[i];
            
            if (newRow[i] == 2048 && !hasWon2048) {
                hasWon2048 = true;
            }
            
            // Shift remaining tiles left
            for (uint8_t j = i + 1; j < BOARD_SIZE - 1; j++) {
                newRow[j] = newRow[j + 1];
            }
            newRow[BOARD_SIZE - 1] = 0;
            moved = true;
        }
    }
    
    // Copy back to original row
    memcpy(row, newRow, sizeof(newRow));
    
    return moved;
}

bool GameBoard::isGameOver() {
    // Check if there are empty tiles
    if (getEmptyTileCount() > 0) {
        return false;
    }
    
    // Check if any moves are possible
    return !canMove();
}

bool GameBoard::canMove() const {
    // Check horizontal merges
    for (uint8_t row = 0; row < BOARD_SIZE; row++) {
        for (uint8_t col = 0; col < BOARD_SIZE - 1; col++) {
            if (board[row][col] == board[row][col + 1]) {
                return true;
            }
        }
    }
    
    // Check vertical merges
    for (uint8_t row = 0; row < BOARD_SIZE - 1; row++) {
        for (uint8_t col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == board[row + 1][col]) {
                return true;
            }
        }
    }
    
    return false;
}

bool GameBoard::hasWon() {
    return hasWon2048;
}

uint16_t GameBoard::getTile(uint8_t row, uint8_t col) const {
    if (row < BOARD_SIZE && col < BOARD_SIZE) {
        return board[row][col];
    }
    return 0;
}

uint32_t GameBoard::getScore() const {
    return score;
}

uint8_t GameBoard::getEmptyTileCount() const {
    uint8_t count = 0;
    for (uint8_t row = 0; row < BOARD_SIZE; row++) {
        for (uint8_t col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == 0) {
                count++;
            }
        }
    }
    return count;
}

void GameBoard::setTile(uint8_t row, uint8_t col, uint16_t value) {
    if (row < BOARD_SIZE && col < BOARD_SIZE) {
        board[row][col] = value;
    }
}

void GameBoard::printBoard() const {
    // This would be used for debugging on PC
    // In embedded system, you might output to UART or ignore
}
