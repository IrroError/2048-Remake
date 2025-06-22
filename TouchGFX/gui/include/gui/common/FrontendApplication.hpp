#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>

class FrontendHeap;

using namespace touchgfx;

class FrontendApplication : public FrontendApplicationBase
{
public:
    FrontendApplication(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplication() { }

    virtual void handleTickEvent()
    {
        model.tick();
        FrontendApplicationBase::handleTickEvent();
    }
    
    // Endgame data methods
    void setEndGameData(int finalScore, bool gameWon);
    int getEndGameScore() const { return endGameScore; }
    bool getEndGameWon() const { return endGameWon; }
    
    // Highest score methods
    int getHighestScore() const { return highestScore; }
    void updateHighestScore(int newScore);
    
private:
    int endGameScore;
    bool endGameWon;
    static int highestScore; // Static to persist across game sessions
};

#endif // FRONTENDAPPLICATION_HPP
