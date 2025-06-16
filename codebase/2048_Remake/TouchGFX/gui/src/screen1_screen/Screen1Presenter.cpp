#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{
    // Initialize the view with the current game state from the model
    updateGameDisplay(model->getGameBoard());
    
    // For STM32 hardware build, the following line would be used:
    // extern void gameApp_setPresenter(void* presenter);
    // gameApp_setPresenter(this);
}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::updateGameDisplay(const GameBoard& gameBoard)
{
    view.updateGameBoard(gameBoard);
    view.updateScore(gameBoard.getScore());
}

void Screen1Presenter::updateScore(uint32_t score)
{
    view.updateScore(score);
}

void Screen1Presenter::simulatorTick()
{
    // Update game board from the model
    GameBoard& gameBoard = model->getGameBoard();
    
    // For the simulator, we can add some random updates
    // Update score and display
    view.updateGameBoard(gameBoard);
    view.updateScore(gameBoard.getScore());
}

void Screen1Presenter::showGameOver()
{
    view.showGameOver();
}

void Screen1Presenter::showGameWon()
{
    view.showGameWon();
}

void Screen1Presenter::hideGameOverWon()
{
    view.hideGameOverWon();
}
