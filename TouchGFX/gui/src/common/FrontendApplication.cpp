#include <gui/common/FrontendApplication.hpp>

// Initialize static highest score
int FrontendApplication::highestScore = 0;

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap), endGameScore(0), endGameWon(false)
{

}

void FrontendApplication::setEndGameData(int finalScore, bool gameWon)
{
    endGameScore = finalScore;
    endGameWon = gameWon;
    
    // Update highest score if this score is higher
    updateHighestScore(finalScore);
}

void FrontendApplication::updateHighestScore(int newScore)
{
    if (newScore > highestScore) {
        highestScore = newScore;
    }
}
