#ifndef BOARD_HPP
#define BOARD_HPP

#include <gui_generated/containers/BoardBase.hpp>

class Board : public BoardBase
{
public:
    Board();
    virtual ~Board() {}
    virtual void initialize();
    void updateDisplay(int row, int col, int value);
    void setRandomTile();
    int getValue(int row, int col) const;
protected:
    touchgfx::Container* getContainer(int row, int col);
    touchgfx::TextAreaWithOneWildcard* getTextArea(int row, int col);
private:
    static int board[4][4];
    static touchgfx::Unicode::UnicodeChar textBuffers[16][10];
    void addRandomTile();
};

#endif // BOARD_HPP
