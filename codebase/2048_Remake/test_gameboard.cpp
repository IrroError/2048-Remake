#include "GameBoard.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

// Helper function to print the board
void printBoard(const GameBoard& board) {
    std::cout << "+------+------+------+------+" << std::endl;
    for (int row = 0; row < 4; row++) {
        std::cout << "|";
        for (int col = 0; col < 4; col++) {
            uint16_t value = board.getTile(row, col);
            if (value == 0) {
                std::cout << "      |";
            } else {
                std::cout << std::setw(5) << value << " |";
            }
        }
        std::cout << std::endl;
        std::cout << "+------+------+------+------+" << std::endl;
    }
    std::cout << "Score: " << board.getScore() << std::endl << std::endl;
}

// Test specific game scenarios
void testGameLogic() {
    std::cout << "=== Testing Game Logic ===" << std::endl;
    
    GameBoard board;
    
    // Test 1: Manual tile placement and merging
    std::cout << "Test 1: Manual tile setup and left merge" << std::endl;
    board.setTile(0, 0, 2);
    board.setTile(0, 1, 2);
    board.setTile(0, 2, 4);
    board.setTile(0, 3, 4);
    printBoard(board);
    
    bool moved = board.moveLeft();
    std::cout << "After move left (should merge 2+2=4, 4+4=8):" << std::endl;
    printBoard(board);
    std::cout << "Move successful: " << (moved ? "Yes" : "No") << std::endl << std::endl;
    
    // Test 2: Vertical movement
    std::cout << "Test 2: Vertical movement" << std::endl;
    board.resetGame();
    board.setTile(0, 0, 2);
    board.setTile(1, 0, 2);
    board.setTile(2, 0, 4);
    printBoard(board);
    
    moved = board.moveUp();
    std::cout << "After move up:" << std::endl;
    printBoard(board);
    
    // Test 3: No valid moves
    std::cout << "Test 3: Testing full board scenario" << std::endl;
    board.resetGame();
    // Fill board with alternating pattern
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            board.setTile(row, col, (row + col) % 2 == 0 ? 2 : 4);
        }
    }
    printBoard(board);
    std::cout << "Can move: " << (board.canMove() ? "Yes" : "No") << std::endl;
    std::cout << "Game over: " << (board.isGameOver() ? "Yes" : "No") << std::endl;
}

// Interactive testing
void interactiveTest() {
    std::cout << "=== Interactive Test ===" << std::endl;
    std::cout << "Commands: w(up), s(down), a(left), d(right), r(reset), q(quit)" << std::endl;
    
    GameBoard board;
    printBoard(board);
    
    char input;
    while (std::cin >> input) {
        bool moved = false;
        
        switch (input) {
            case 'w': moved = board.moveUp(); break;
            case 's': moved = board.moveDown(); break;
            case 'a': moved = board.moveLeft(); break;
            case 'd': moved = board.moveRight(); break;
            case 'r': 
                board.resetGame();
                moved = true;
                std::cout << "Game reset!" << std::endl;
                break;
            case 'q': return;
            default: 
                std::cout << "Invalid command!" << std::endl;
                continue;
        }
        
        printBoard(board);
        
        if (board.hasWon()) {
            std::cout << "🎉 YOU WON! You reached 2048!" << std::endl;
        }
        
        if (board.isGameOver()) {
            std::cout << "💀 GAME OVER! No more moves possible." << std::endl;
            std::cout << "Final Score: " << board.getScore() << std::endl;
            break;
        }
        
        if (!moved && input != 'r') {
            std::cout << "No tiles moved!" << std::endl;
        }
    }
}

// Simple test function to verify GameBoard functionality
void testGameBoard() {
    std::cout << "=== 2048 Game Board Test ===" << std::endl;
    
    // Initialize random seed
    srand(time(nullptr));
    
    // Create game board
    GameBoard board;
    
    std::cout << "Initial board state:" << std::endl;
    printBoard(board);
    
    // Test basic moves
    std::cout << "Testing random moves..." << std::endl;
    
    for (int i = 0; i < 5; i++) {
        Direction dirs[] = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
        Direction randomDir = dirs[rand() % 4];
        
        bool moved = board.move(randomDir);
        std::cout << "Move " << i+1 << " result: " << (moved ? "Success" : "No change") << std::endl;
        printBoard(board);
        
        if (board.isGameOver()) {
            std::cout << "Game over reached!" << std::endl;
            break;
        }
    }
    
    std::cout << "=== Test Complete ===" << std::endl;
}

int main() {
    std::cout << "Choose test mode:" << std::endl;
    std::cout << "1. Automated tests" << std::endl;
    std::cout << "2. Logic-specific tests" << std::endl;
    std::cout << "3. Interactive game" << std::endl;
    std::cout << "Enter choice (1-3): ";
    
    int choice;
    std::cin >> choice;
    
    switch (choice) {
        case 1:
            testGameBoard();
            break;
        case 2:
            testGameLogic();
            break;
        case 3:
            interactiveTest();
            break;
        default:
            std::cout << "Invalid choice, running automated tests..." << std::endl;
            testGameBoard();
    }
    
    return 0;
}
