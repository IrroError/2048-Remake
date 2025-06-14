#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{
    // Connect this presenter to the game app
    extern void gameApp_setPresenter(void* presenter);
    gameApp_setPresenter(this);
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
