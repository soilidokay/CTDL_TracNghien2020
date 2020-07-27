#ifndef Lable_H
#define Lable_H

#include "Window.h"

using namespace scl;

class Label : public window
{
public:
	void setBoder(bool value) { _boder = value; }
	void settext(std::string text) { _Text = text; }
	void UpdateText(std::string text) {
		_Text = text;
		showText();
	}
	void show()override {

		if (_boder) Draw();
		showText();
	}
	void showText() {
		scl::TextColor(_hScreen, getcolor());
		gotoXY(_hScreen, getx() + 1, gety() + 1);
		std::cout<<std::setfill(' ');
		std::cout << std::setw(getwidth()) << " ";
		gotoXY(_hScreen, getx() + 1, gety() + 1);
		std::cout << _Text.substr(0, getwidth());
	}
	Label(int width, int height, int x, int y) : window(width, height, x, y)
	{
		_boder = 0;
		_Text = "lable!!";
	}

	~Label()
	{
	}
private:
	bool _boder;
	std::string _Text;
};


#endif // !Lable_H

