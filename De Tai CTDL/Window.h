#ifndef window_h
#define window_h

#include "console.h"
#include <iomanip>
#include "CompareData.h"
using namespace scl;

class window :public CompareData<int>
{
public:
	typedef void(window::* backupform)();
	window(int width, int height, int x, int y);
	~window();
	virtual void show() { Draw(); }
	virtual void SetActive(bool isActive) {};
	virtual void action(EventConsole& evt) { KeyMouse(&evt); }
	void setwidth(int width) { _width = width; }
	void setheight(int height) { _height = height; }
	void setx(int x) { _x = x; }
	void sety(int y) { _y = y; }
	void setId(int id) { _id = id; }
	void setColor(int color) { _color = color; }
	void setEvent(int** area, int maxX, int maxY) {
		_area = area;
		maxX = (maxX < _width) ? maxX : _width;
		maxY = (maxY < _height) ? maxY : _height;
		for (int y = _y; y < _y + maxY + 2; ++y) {
			for (int x = _x; x < _x + maxX + 2; ++x) {
				_area[y][x] = _id;
				//gotoXY(x, y); std::cout << _area[y][x];
			}
			//_getch();
		}
	}
	void setselect(int select) { _select = select; }
	virtual void SetScreen(HANDLE hscreen);
	unsigned int getselect() { return _select; }
	void setArea(int** a) { _area = a; }
	int getwidth() { return _width; }
	int getheight() { return _height; }
	int getx() { return _x; }
	int gety() { return _y; }
	int getcolor() { return _color; }
	int getId() override { return _id; }
	bool checkACtive(StatusMouse& sMouse)
	{
		return _area[sMouse.y][sMouse.x] == _id;
	}
protected:
	void ouput(char ch1, char ch2, char chFill) {
		//std::set_new_handler
		std::cout << std::setfill(chFill);
		std::cout << std::left;
		std::cout << std::setw(_width + 1) << ch1 << ch2;
	}
	void Draw(int color = -1) {
		if (color == -1) {
			color = _color;
		}
		scl::TextColor(_hScreen, color);
		gotoXY(_hScreen,_x, _y);
		ouput((char)218, (char)191, (char)196);
		for (int i = 0; i < _height;) {
			gotoXY(_hScreen,_x, _y + ++i);
			ouput((char)179, (char)179, ' ');
		}
		gotoXY(_hScreen,_x, _height + _y + 1);
		ouput((char)192, (char)217, (char)196);
	}

protected:
	int _select;
	HANDLE _hScreen;
private:
	int _height, _width;
	int _color;
	int _x, _y;
	int _id = 0;
	int** _area;
};
#endif // !window_h

