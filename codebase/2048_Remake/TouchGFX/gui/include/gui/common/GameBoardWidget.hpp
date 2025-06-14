#ifndef GAMEBOARDWIDGET_HPP
#define GAMEBOARDWIDGET_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <gui/common/TileWidget.hpp>
#include "GameBoard.hpp"

using namespace touchgfx;

class GameBoardWidget : public Container
{
public:
    GameBoardWidget();
    virtual ~GameBoardWidget() {}

    // Update the board display from the game logic
    void updateFromGameBoard(const GameBoard& gameBoard);
    
    // Setup the board layout
    void setupBoard(int16_t x, int16_t y);
      // Animation methods
    void animateMove(GameDirection direction);
    void animateNewTile(uint8_t row, uint8_t col);

protected:
    static const int16_t BOARD_SIZE = 4;
    static const int16_t TILE_SIZE = 60;
    static const int16_t TILE_MARGIN = 8;
    static const int16_t BOARD_PADDING = 10;
    
    Box boardBackground;
    TileWidget tiles[BOARD_SIZE][BOARD_SIZE];
    
    // Helper methods
    void initializeTiles();
    void updateTilePositions();
};

#endif // GAMEBOARDWIDGET_HPP
