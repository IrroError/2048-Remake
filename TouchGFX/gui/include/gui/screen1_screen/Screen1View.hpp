#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void handleJoystickUp();
    void handleJoystickDown();
    void handleJoystickLeft();
    void handleJoystickRight();
    void handleResetGame();
    void handleTickEvent() override;
    void tickEvent() override;
    static Screen1View* instance;
    Screen1View* getInstance();
protected:
private:
};
#endif // SCREEN1VIEW_HPP
