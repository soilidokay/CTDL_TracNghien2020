#ifndef InPutBox_H
#define InPutBox_H
#include <iostream>
#include "Window.h"
#include <string>

using namespace scl;

class InPutBox : public window
{
public:
	void action(EventConsole&)override;
	void setText(std::string Str) {
		_strtext = Str;
		showText();
	}
	void SetisNumber(bool isNumber) { _isNumber = isNumber; }
	void setPassChar(char passchar) {
		_password = passchar;
	}
	bool isEmpty() { return _strtext.length() < 1; }
	char getpassChar() { return _password; }
	void show()override {
		window::show();
		showText();
	}
	void showText() {
		TextColor(_hScreen, color_black | colorbk_white);
		gotoXY(_hScreen, getx() + 1, gety() + 1);
		std::cout << std::left << std::setfill(' ');
		if (_password == NULL) std::cout << std::setw(getwidth()) << _strtext;
		else if (_strtext.length() > 0) {
			std::cout << std::setfill(_password) << std::setw(_strtext.length()) << _password;
		}
	}
	bool isNumber() { return _isNumber; }
	void SetActive(bool isActive) override;
	std::string Gettext() { return _strtext; }
	InPutBox(int width, int height, int x, int y);
	~InPutBox();
private:
	bool checkkey(int key) {
		return key != key_tab && key != 27 && key != key_Enter;
	}
	void processkey(int key);
	void writeChar(char key) {
		int lentext = _strtext.length();
		gotoXY(_hScreen,getx() + lentext, gety() + 1);
		if (_password == NULL)	std::cout << char(key);
		else std::cout << _password;

	}
	void backspace() {
		if (_strtext.length() > 0) {
			std::cout << "\b \b";
			_strtext.erase(_strtext.length() - 1, 1);
		}
	}
	char _password;
	bool _isNumber = false;
	std::string _strtext;
};

#endif // !InPutBox_H



