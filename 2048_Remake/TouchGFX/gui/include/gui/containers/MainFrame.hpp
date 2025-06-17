#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <gui_generated/containers/MainFrameBase.hpp>

class MainFrame : public MainFrameBase
{
public:
    MainFrame();
    virtual ~MainFrame() {}

    virtual void initialize();
protected:
};

#endif // MAINFRAME_HPP
