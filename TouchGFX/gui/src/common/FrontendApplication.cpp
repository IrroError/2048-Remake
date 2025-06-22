#include <gui/common/FrontendApplication.hpp>

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap), endGameScore(0), endGameWon(false)
{

}

void FrontendApplication::setEndGameData(int finalScore, bool gameWon)
{
    endGameScore = finalScore;
    endGameWon = gameWon;
}
