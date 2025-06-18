#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <gui_generated/containers/MainFrameBase.hpp>

class MainFrame: public MainFrameBase {
public:
	MainFrame();
	virtual ~MainFrame() {
	}
	virtual void initialize();
	void setScore(int score);

	typedef void (*ResetCallback)();

	void setResetCallback(ResetCallback callback) {
		resetCallback = callback;
	}

	virtual void handleResetButtonClicked() override {
		if (resetCallback) {
			resetCallback();
		}
	}
protected:
private:
	static touchgfx::Unicode::UnicodeChar scoreBuffer[6];
	ResetCallback resetCallback;
};

#endif // MAINFRAME_HPP
