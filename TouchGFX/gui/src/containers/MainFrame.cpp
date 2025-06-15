#include <gui/containers/MainFrame.hpp>

touchgfx::Unicode::UnicodeChar MainFrame::scoreBuffer[6];
MainFrame::MainFrame()
{

}

void MainFrame::initialize()
{
    MainFrameBase::initialize();
}

void MainFrame::setScore(int score)
{
	touchgfx::TextAreaWithOneWildcard* currentScore = &Score;
	touchgfx::Unicode::snprintf(scoreBuffer, 6, "%d", score);
	currentScore->setWildcard(scoreBuffer);
	currentScore->invalidate();
}
