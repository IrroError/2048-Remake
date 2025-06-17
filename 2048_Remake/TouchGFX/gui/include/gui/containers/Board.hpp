#ifndef BOARD_HPP
#define BOARD_HPP

#include <gui_generated/containers/BoardBase.hpp>

class Board : public BoardBase
{
public:
    Board();
    virtual ~Board() {}

    virtual void initialize();
protected:
};

#endif // BOARD_HPP
