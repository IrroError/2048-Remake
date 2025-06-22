#ifndef ENDGAMEFRAME_HPP
#define ENDGAMEFRAME_HPP

#include <gui_generated/containers/EndGameFrameBase.hpp>

class EndGameFrame : public EndGameFrameBase
{
public:
    EndGameFrame();
    virtual ~EndGameFrame() {}

    virtual void initialize();
    
    // Public methods to access UI elements
    void setCurrentScore(touchgfx::Unicode::UnicodeChar* buffer);
    void setHighestScore(touchgfx::Unicode::UnicodeChar* buffer);
    void setTitleMessage(touchgfx::Unicode::UnicodeChar* buffer);
    
protected:
};

#endif // ENDGAMEFRAME_HPP
