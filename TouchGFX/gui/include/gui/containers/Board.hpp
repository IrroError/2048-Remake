#ifndef BOARD_HPP
#define BOARD_HPP

#include <gui_generated/containers/BoardBase.hpp>

class Board: public BoardBase {
public:
	Board();
	virtual ~Board() {
	}
	virtual void initialize();
	void updateDisplay(int row, int col, int value);
	int getValue(int row, int col) const;
	int getScore();
	void randomTile();
	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();
	bool canMove();
	void mySrand(uint32_t s);
	uint32_t myRand();
	void clearBoard();
protected:
	touchgfx::Container* getContainer(int row, int col);
	touchgfx::TextAreaWithOneWildcard* getTextArea(int row, int col);
private:
	static int board[4][4];
	static touchgfx::Unicode::UnicodeChar textBuffers[16][10];
	static uint32_t seed;
};

#endif // BOARD_HPP
