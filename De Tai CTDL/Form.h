#ifndef Form_H
#define Form_H
#include <iostream>
#include "Database.h"
#include "checkbox.h"
#include "Button.h"
#include "console.h"
#include "InPutBox.h"
#include "Lable.h"
#include "TimeClock.h"
#include "Window.h"
#include "CheckList.h"
#include "warning.h"
#include "TreeAVL.h"
#include <functional>
#include "EventController.h"
#include "outbuf.h"
#include "AppDbContext.h"
using namespace scl;
using namespace std::placeholders;
bool ShowWarning(HANDLE _hSCreen, std::string text, bool isCancel = false);
class Form
{

public:
	typedef void (Form::* Backupform)();
	Form(Form* Fbackup, int width, int height, int bkcolor);

	void setwidth(int width) { _width = width; }
	void setheight(int height) { _height = height; }
	int getwidth() { return _width; }
	int getheight() { return _height; }
	int checkmoue() {
		return _area[evt._Smouse.x][evt._Smouse.y];
	}
	virtual	void constructor() = 0;
	void init() {
		_hSCreen = CreateScreenBuff();
		_StreamBuff = new outbuf(_hSCreen);
		Events->setScreen(_hSCreen);
		std::cout.rdbuf(_StreamBuff);

		scl::ShowCur(_hSCreen, false);
		scl::SetTitle("tai nguyen");
		scl::SizeConsole(_hSCreen, _width, _height);
		scl::fillBackGround(_hSCreen, _width, _height, _bkcolor);
		_Context = AppDbContext::getInstance();
	}
	void backup() {
		//init();
		std::cout.rdbuf(_StreamBuff);
		//show();
	}
	virtual void show() {

		SetConsoleActiveScreenBuffer(_hSCreen);
	}
	void setEventMouseOrKey() {
		for (int i = 0; i < nObj; i++) {
			Showobj[i]->setId(i);
			Showobj[i]->setEvent(_area, _width, _height);
		}
	}
	void Close();
	~Form();

protected:
	int getCirNum(int start, int end, int num) {
		if (num < end) return ++num;
		else if (num == end) return start;
		return start;
	}
	void DrawToScreen();
protected:
	outbuf* _StreamBuff;
	HANDLE _hSCreen;
	bool stop = 1;
	window* *Showobj;
	int nObj;
	EventConsole evt;
	int _bkcolor;
	int** _area;
	EventMouseOrKey* Events;
	AppDbContext* _Context = NULL;
private:
	int _width;
	int _height;
	Form* _Fbackup;
};

#endif // !Form_H
