#ifndef GAMEBOARDWIDGET_HPP
#define GAMEBOARDWIDGET_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <gui/common/TileWidget.hpp>

// Include the core GameBoard header
#include "GameBoard.hpp"

// We're now using GameDirection from the Core/Inc/GameBoard.hpp

using namespace touchgfx;

class GameBoardWidget : public Container
{
public:
    GameBoardWidget();
    virtual ~GameBoardWidget() {}

    // Update the board display from the game logic
    void updateFromGameBoard(const GameBoard& gameBoard);
      // Update individual tile for testing/simulation
    void updateTile(int row, int col, uint16_t value);
    
    // Setup the board layout
    void setupBoard(int16_t x, int16_t y);
    
    // Get the board's width in pixels
    int16_t getBoardWidth() const;
    
    // Animation methods
    void animateMove(GameDirection direction);
    void animateNewTile(uint8_t row, uint8_t col);

protected:    static const int16_t BOARD_SIZE = 4;
    static const int16_t TILE_SIZE = 40;     // Reduced size to fit gameBoardContainer
    static const int16_t TILE_MARGIN = 5;    // Margin between tiles
    static const int16_t BOARD_PADDING = 5;  // Padding around the board
    
    Box boardBackground;
    TileWidget tiles[BOARD_SIZE][BOARD_SIZE];
    
private:
    // Tile management
    void initializeTiles();
    void setupTestData();
};

#endif // GAMEBOARDWIDGET_HPP
