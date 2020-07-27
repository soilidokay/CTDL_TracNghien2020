#ifndef TimeClock_H
#define TimeClock_H

#include "console.h"
#include <Windows.h>
#include <thread>
#include "EventController.h"
#include <functional>

typedef std::function<void()>   ACTIONTIMECLOCK;

typedef struct  Hour
{
	int _hour;
	int	_minute;
	int _second;
	Hour(int hour, int minute, int second) {
		_hour = hour;
		_minute = minute;
		_second = second;
	}
} *pHour;

class TimeClock
{

public:
	TimeClock(Hour hour, int color, int x, int y) {
		_hour = new Hour(hour);
		_x = x;
		_y = y;
		_color = color;
		_stop = 0;
		actionEnd = NULL;
	}
	~TimeClock() {
		_stop = 0;
	}
	void printClock(bool (TimeClock::* changetime)(pHour)) {
		std::string _strHour = "00:00:00";
		_stop = 1;
		insertarray(_strHour, _hour);
		WriteBlockChar(_strHour);
		while (_stop)
		{
			Sleep(990);
			if (!(this->*changetime)(_hour)) _stop = 0;
			insertarray(_strHour, _hour);
			WriteBlockChar(_strHour);
		}
		if (actionEnd != NULL) {
			actionEnd();
		}
		return;
	}
	void SetOnEnd(ACTIONTIMECLOCK action) {
		actionEnd = action;
	}
	bool changetimePlus(pHour hour) {
		if (hour->_second < 59) ++hour->_second;
		else if (hour->_minute < 59) {
			hour->_second = 0;
			++hour->_minute;
		}
		else if (hour->_hour < 23)
		{
			++hour->_hour;
			hour->_minute = 0;
			hour->_second = 0;
		}
		else {
			hour->_hour = 0;
			hour->_minute = 0;
			hour->_second = 0;
		}
		return 1;
	}
	bool changetimeMult(pHour hour) {
		if (hour->_second > 0) --hour->_second;
		else if (hour->_minute > 0) {
			hour->_second = 59;
			--hour->_minute;
		}
		else if (hour->_hour > 0)
		{
			--hour->_hour;
			hour->_minute = 59;
			hour->_second = 59;
		}
		else return 0;
		return 1;
	}
	void close(DWORD evt) {
		if (evt == CTRL_CLOSE_EVENT) _stop = 0;
	}
	void stop() {
		Sleep(100);
		_stop = 0;
	}

private:
	void insertarray(std::string& strHour, pHour hour) {
		int bait = 0;
		bait = hour->_second;
		strHour[7] = inToA(bait % 10);
		strHour[6] = inToA(bait /= 10);

		bait = hour->_minute;
		strHour[4] = inToA(bait % 10);
		strHour[3] = inToA(bait /= 10);

		bait = hour->_hour;
		strHour[1] = inToA(bait % 10);
		strHour[0] = inToA(bait /= 10);

	}

	void WriteBlockChar(std::string& _strHour)
	{
		EventController* handle = EventController::getInstance();

		CHAR_INFO charater[8];
		for (int i = 0; i < 8; i++) {
			charater[i].Attributes = _color;
			charater[i].Char.AsciiChar = _strHour[i];
		}
		COORD sizebuff = { 8,1 };
		COORD pos = { 0,0 };
		SMALL_RECT earea = { (SHORT)_x,(SHORT)_y,(SHORT)_x + 8 - 1,(SHORT)_y + 1 - 1 };
		WriteConsoleOutput(handle->getScreenActive(), charater, sizebuff, pos, &earea);
	}
	char inToA(int h) {
		switch (h)
		{
		case 0:return '0';
		case 1:return '1';
		case 2:return '2';
		case 3:return '3';
		case 4:return '4';
		case 5:return '5';
		case 6:return '6';
		case 7:return '7';
		case 8:return '8';
		case 9:return '9';
		default:
			return -1;
			break;
		}

	}
	ACTIONTIMECLOCK actionEnd;
	pHour _hour;
	bool _stop;
	int _x, _y, _color;
};

#endif //! TimeClock_H