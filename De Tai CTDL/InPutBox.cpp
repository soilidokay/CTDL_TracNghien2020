#include "InPutBox.h"


void InPutBox::action(EventConsole& evt)
{
	if (evt.isKeyEvent()) {
		processkey(evt._key);
	}
	//scl::ShowCur(true);
	//TextColor(color_black | colorbk_cyan);
	//scl::ShowCur(false);
}

void InPutBox::processkey(int key)
{
	switch (key)
	{
	case key_bkspace: backspace(); break;
	default:
		if (_isNumber) {
			if (key > 47 && key < 58) {
				int lentext = _strtext.length() + 1;
				if (lentext < getwidth()) {
					_strtext += char(key);
					writeChar(key);
				}
			}
		}
		else if (key > 31 && key < 127) {
			int lentext = _strtext.length() + 1;
			if (lentext < getwidth()) {
				_strtext += char(key);
				writeChar(key);
			}
		}
		break;
	}

}

void InPutBox::SetActive(bool isActive)
{
	scl::ShowCur(_hScreen, isActive);
	if (isActive) {

		TextColor(_hScreen, color_black | colorbk_white);
		gotoXY(_hScreen, getx() + _strtext.length() + 1, gety() + 1);
	}
}

InPutBox::InPutBox(int width, int height, int x, int y) : window(width, height, x, y)
{
	_password = NULL;
}


InPutBox::~InPutBox()
{
}
