#ifndef MODEL_HPP
#define MODEL_HPP

#include "GameBoard.hpp"

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    
    // Get access to the game board
    GameBoard& getGameBoard() { return gameBoard; }
    
protected:
    ModelListener* modelListener;
    GameBoard gameBoard; // Main game board instance
};

#endif // MODEL_HPP
