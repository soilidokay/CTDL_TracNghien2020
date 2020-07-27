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
	void setTextCenter(bool isCenter) {
		textCenter = isCenter;
	}
	void show()override {
		int color = gettxtColor(_hScreen);
		Draw();
		showText();
		TextColor(_hScreen, color);
	}
	void showText() {
		if (textCenter) {
			gotoXY(_hScreen, getx() + getwidth() / 2 - _strText.length() / 2 + 1, gety() + 1);
		}
		else {
			gotoXY(_hScreen, getx() + 1, gety() + 1);
		}
		TextColor(_hScreen, color_darkgreen | colorbk_darkwhite);
		std::cout << _strText.substr(0, getwidth());
	}
	Button(int width, int height, int x, int y) : window(width, height, x, y)
	{
		setColor(color_darkwhite | colorbk_darkwhite);
		_strText = "button!";
	}
	void UpdateText(std::string text) {
		_strText = text;
		TextColor(_hScreen, color_darkgreen | colorbk_darkwhite);

		if (textCenter) {
			gotoXY(_hScreen, getx() + getwidth() / 2 - _strText.length() / 2 + 1, gety() + 1);
		}
		else {
			gotoXY(_hScreen, getx() + 1, gety() + 1);
		}
		std::cout << std::setfill(' ');
		std::cout << std::setw(getwidth()) << " ";
		if (textCenter) {
			gotoXY(_hScreen, getx() + getwidth() / 2 - _strText.length() / 2 + 1, gety() + 1);
		}
		else {
			gotoXY(_hScreen, getx() + 1, gety() + 1);
		}
		std::cout << _strText.substr(0, getwidth());
	}
	void setText(std::string text) {
		_strText = text;
	}
	void UpdateBackGround(int colorbk) {
		int colorword = getcolor() & 0x0000000f;
		int color = gettxtColor(_hScreen);
		Draw(colorword | colorbk);
		showText();
		TextColor(_hScreen, color);
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
	bool textCenter = true;
};

#endif // !Button_H

