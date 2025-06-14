#include <gui/common/GameBoardWidget.hpp>
#include <touchgfx/Color.hpp>

GameBoardWidget::GameBoardWidget()
{
    int16_t boardWidth = BOARD_SIZE * TILE_SIZE + (BOARD_SIZE - 1) * TILE_MARGIN + 2 * BOARD_PADDING;
    int16_t boardHeight = boardWidth; // Square board
    
    setWidth(boardWidth);
    setHeight(boardHeight);
    
    // Setup board background
    boardBackground.setPosition(0, 0, boardWidth, boardHeight);
    boardBackground.setColor(Color::getColorFromRGB(187, 173, 160)); // Board background color
    add(boardBackground);
    
    // Initialize and position tiles
    initializeTiles();
}

void GameBoardWidget::setupBoard(int16_t x, int16_t y)
{
    setPosition(x, y, getWidth(), getHeight());
}

void GameBoardWidget::initializeTiles()
{
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            int16_t tileX = BOARD_PADDING + col * (TILE_SIZE + TILE_MARGIN);
            int16_t tileY = BOARD_PADDING + row * (TILE_SIZE + TILE_MARGIN);
            
            tiles[row][col].setupTile(tileX, tileY, TILE_SIZE, TILE_SIZE);
            tiles[row][col].setValue(0); // Start with empty tiles
            add(tiles[row][col]);
        }
    }
}

void GameBoardWidget::updateFromGameBoard(const GameBoard& gameBoard)
{
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            uint16_t value = gameBoard.getTile(row, col);
            tiles[row][col].setValue(value);
        }
    }
    invalidate();
}

void GameBoardWidget::animateMove(GameDirection direction)
{
    // For now, just update without animation
    // In a full implementation, you would animate tiles sliding
    // This requires more complex TouchGFX animation setup
}

void GameBoardWidget::animateNewTile(uint8_t row, uint8_t col)
{
    if (row < BOARD_SIZE && col < BOARD_SIZE) {
        tiles[row][col].animateSpawn();
    }
}
