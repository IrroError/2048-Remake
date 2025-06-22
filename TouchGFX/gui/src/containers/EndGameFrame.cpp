#include <gui/containers/EndGameFrame.hpp>

EndGameFrame::EndGameFrame()
{

}

void EndGameFrame::initialize()
{
    EndGameFrameBase::initialize();
}

void EndGameFrame::setCurrentScore(touchgfx::Unicode::UnicodeChar* buffer)
{
    Score.setWildcard(buffer);
    Score.invalidate();
}

void EndGameFrame::setHighestScore(touchgfx::Unicode::UnicodeChar* buffer)
{
    Highest_Score.setWildcard(buffer);
    Highest_Score.invalidate();
}

void EndGameFrame::setTitleMessage(touchgfx::Unicode::UnicodeChar* buffer)
{
    // Use setText to directly set the text instead of setWildcard
    // since the text resource doesn't have a proper wildcard
    You_win_or_Nice_try.setWildcard(buffer);
    You_win_or_Nice_try.invalidate();
}
