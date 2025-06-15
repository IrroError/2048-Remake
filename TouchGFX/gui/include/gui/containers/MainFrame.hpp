#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <gui_generated/containers/MainFrameBase.hpp>

class MainFrame : public MainFrameBase
{
public:
    MainFrame();
    virtual ~MainFrame() {}
    virtual void initialize();
    void setScore(int score);
protected:
private:
    static touchgfx::Unicode::UnicodeChar scoreBuffer[6];
};

#endif // MAINFRAME_HPP
