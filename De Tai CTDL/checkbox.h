#ifndef checkbox_H
#define checkbox_H

#include "Window.h"

class checkbox :public window
{
public:

	checkbox(int x, int y) :window(1, 1, x, y)
	{
		select = 0;
	}
	void showText() {
		TextColor(_hScreen, getcolor());
		gotoXY(_hScreen, getx() + 1, gety() + 1);
		if (select) std::cout << '0';
		else std::cout << ' ';
	}
	bool getChck() { return select; }
	void setChck(bool sec) {
		select = sec;
		showText();
	}

	void action(EventConsole& evt)override {
		if (select) select = 0;
		else select = 1;
		showText();
	}
	~checkbox()
	{
	}
private:
	bool select;
};
#endif // !checkbox_H

