#ifndef Button_H
#define Button_H

#include "Window.h"
#include <functional>

using namespace scl;
typedef std::function<void(EventConsole& evt)>   ACTIONBUTTON;

class Button : public window
{
public:
	void action(EventConsole& evt) override {
		if (!evt.isMouseEvent()) return;
		scl::ShowCur(false);
		_select = 1;
		setColor(color_darkwhite | colorbk_white);
		show();
		Sleep(200);
		setColor(color_darkwhite | colorbk_darkwhite);
		show();
		evt.reset();
		if (actionButton)actionButton(evt);
	}

	void show()override {
		int color = gettxtColor(_hScreen);
		TextColor(_hScreen, getcolor());
		Draw();
		showText();
		TextColor(_hScreen, color);
	}
	void showText() {
		gotoXY(_hScreen, getx() + getwidth() / 2 - _strText.length() / 2 + 1, gety() + 1);
		TextColor(_hScreen, color_darkgreen|colorbk_darkwhite);
		std::cout << _strText.substr(0, getwidth());
	}
	Button(int width, int height, int x, int y) : window(width, height, x, y)
	{
		setColor(color_darkwhite | colorbk_darkwhite);
		_strText = "button!";
	}
	void setText(std::string text) {
		_strText = text;
	}
	void setActionButton(const ACTIONBUTTON& func) {
		actionButton = func;
	}
	~Button()
	{
	}
private:
	std::string _strText;
	ACTIONBUTTON actionButton;
};

#endif // !Button_H

