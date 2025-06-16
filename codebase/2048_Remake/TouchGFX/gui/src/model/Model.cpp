#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
    // For simulator only - update game state
    static int counter = 0;
    counter++;
    
    // Every 20 ticks, add a small score update for simulation
    if (counter % 20 == 0) {
        // Add small score increment for simulator
        gameBoard.setTile(3, 3, (counter / 20) % 2048);
    }
}
