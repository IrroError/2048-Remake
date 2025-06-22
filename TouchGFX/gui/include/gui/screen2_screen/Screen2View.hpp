#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void setFinalScore(int score);
    void setHighestScore(int score);
    void setGameResult(bool won);
    void handlePlayAgainButtonClicked();
    void handleTickEvent() override;
    void tickEvent();
    
protected:
private:
    int finalScore;
    int highestScore;
    bool gameWon;
    static touchgfx::Unicode::UnicodeChar scoreBuffer[10];
    static touchgfx::Unicode::UnicodeChar highestScoreBuffer[10];
};

#endif // SCREEN2VIEW_HPP 