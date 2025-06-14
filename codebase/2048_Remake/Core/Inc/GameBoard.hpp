#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#ifdef __cplusplus
#include <cstdint>
#include <cstdlib>
#else
#include <stdint.h>
#include <stdlib.h>
#endif

enum class GameDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

class GameBoard {
public:
    static const uint8_t BOARD_SIZE = 4;
    
    GameBoard();
    ~GameBoard() = default;
    
    // Core game methods
    void resetGame();
    bool spawnNewTile();
    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();    bool move(GameDirection direction);
    bool isGameOver();
    bool hasWon();
    
    // Getters
    uint16_t getTile(uint8_t row, uint8_t col) const;
    uint32_t getScore() const;
    bool canMove() const;
    
    // Debug/Testing
    void printBoard() const;
    void setTile(uint8_t row, uint8_t col, uint16_t value); // For testing
    
private:
    uint16_t board[BOARD_SIZE][BOARD_SIZE];
    uint32_t score;
    bool hasWon2048;
    
    // Helper methods
    bool slideAndMergeRow(uint16_t row[BOARD_SIZE]);
    void rotateClockwise();
    void rotateCounterClockwise();    bool canMoveInDirection(GameDirection direction) const;
    uint8_t getEmptyTileCount() const;
    void addRandomTile();
};

#endif // GAMEBOARD_HPP
