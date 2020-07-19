#ifndef ListBox_H
#define ListBox_H

#include "Window.h"
#include <functional>
#include "IList.h"

template<class _T>
class ListBox : public window
{
public:
	typedef std::function<bool(_T*, int)> ACTION;

	ListBox(int width, int height, int x, int y) : window(width, height, x, y)
	{
		gxShow = getx() + 1;
		gyShow = gety() + 4;
	}
	bool _checkmoue(EventConsole& evt) {
		int width = getwidth() + 2;
		int height = getheight() + 2;
		int x = getx();
		int y = gety();
		int xm = evt._Smouse.x;
		int ym = evt._Smouse.y;
		return (xm >= x && xm < x + width) && (ym >= y && ym < y + height);
	}
	void MoveUp(int amount) {
		posPrintInt -= amount;
		if (posPrintInt < 0) posPrintInt = 0;
	}
	void MoveDw(int amount) {
		if (posPrintInt + amount < _listObj->getSize()) {
			posPrintInt += amount;
		}
	}
	virtual void action(EventConsole& evt) {
		if (!evt.isMouseEvent()) return;
		if (BclickBtn(evt) == 1) {
			MoveUp(getheight() - 3);
			showLObj();
		}
		else if (BclickBtn(evt) == 2) {
			MoveDw(getheight() - 3);
			showLObj();
		}
		else
		{
			selectedindex = evt._Smouse.y - gety() - 4 + posPrintInt;
			if (selectedindex>-1 && selectedindex < _listObj->getSize()) {
				showLObj();
				if (actionButton) {
					actionButton(evt);
				}
			}
			else
			{
				selectedindex = -1;
			}
		}

		_select = 1;
	}
	virtual void setStrTiltle(std::string strTiltle) {
		_strTiltle = strTiltle;
	}
	void show()override {
		window::show();
		gotoXY(_hScreen, getx() + getwidth() / 2 - _strTiltle.length() / 2, gety() + 1);
		scl::TextColor(_hScreen, color_darkgreen | colorbk_yellow);
		std::cout << _strTiltle;
		if (getheight() > 9) {
			setUpBtn(getcolor());
			setDwBtn(getcolor());
		}
		showLObj();
	}
	int BclickBtn(EventConsole& evt) {
		int mx = evt._Smouse.x;
		int my = evt._Smouse.y;

		if (BtnClick.x1 == mx && BtnClick.y1 == my) {
			setUpBtn(colorbk_darkcyan);
			Sleep(100);
			setUpBtn(getcolor());
			return 1;
		}
		else if (BtnClick.x2 == mx && BtnClick.y2 == my) {
			setDwBtn(colorbk_darkcyan);
			Sleep(100);
			setDwBtn(getcolor());
			return 2;
		}
		return 0;
	}
	~ListBox()
	{
	}
	void setchose(int chose) {
		selectedindex = chose;
	}
	void setActionButton(const ACTIONBUTTON& func) {
		actionButton = func;
	}
	node<_T>* getPosPrint() { return posPrint; }
	void setListObj(IList<_T>* listObj) {
		_listObj = listObj;
		//selected = posPrint = _listObj->getfirst();
		//showLObj();
		posPrintInt = 0;
	}
	int getIndexSelected() { return selectedindex; }
	void showTitle() {
		TextColor(_hScreen, colorbk_darkblue | color_white);
		gotoXY(_hScreen, getx() + 1, gety() + 3);
		_T::settitle();
	}
	virtual bool showSingle(_T* data, int index) {
		gotoXY(_hScreen, gxShow, gyShow + index - posPrintInt);

		if (index == selectedindex) {
			std::cout << std::setw(3) << index; DrawHight(selectedindex);
		}
		else {
			std::cout << std::setw(3) << index << char(179) << data;
		}

		return true;
	}
	void checkEmptyPage() {
		if (posPrintInt >= _listObj->getSize()) {
			MoveUp(getheight() - 3);
		}
	}
	void showLObj() {
		if (_listObj == NULL) return;
		if (getheight() < 2) return;
		int count = 0;
		_T* temp = NULL;
		showTitle();
		TextColor(_hScreen, getcolor());
		std::cout << std::setfill(' ');
		checkEmptyPage();
		_listObj->forEach([&](_T* data, int index) {return this->showSingle(data, index); },
			posPrintInt, posPrintInt + getheight() - 4);

	}
	void addNode(_T* Dat) {
		if (_listObj->Search(Dat) < 0) {
			int index = _listObj->InsertConst(Dat);
			setchose(index);
			showLObj();
		}
	}
	int DelNode() {
		if (selectedindex > -1) {
			_listObj->Delete(selectedindex);
			showLObj();
		}
		return selectedindex;
	}
	void DrawHight(int index) {
		TextColor(_hScreen, colorbk_cyan | color_white);
		//gotoXY(_hScreen, gxShow, gy);
		std::cout << char(179) << _listObj->GetData(index);
		TextColor(_hScreen, getcolor());
	}
	IList<_T> getDataSource() { return _listObj; }

	_T* getSelected() { return _listObj->GetData(selectedindex); }
protected:
	void setUpBtn(int color) {
		TextColor(_hScreen, color);
		BtnClick.y1 = gety() + getheight() / 2 - 3;
		BtnClick.x1 = getx() + getwidth();
		gotoXY(_hScreen, BtnClick.x1, BtnClick.y1);
		std::cout << char(30);
	}
	void setDwBtn(int color) {
		TextColor(_hScreen, color);
		BtnClick.y2 = gety() + getheight() / 2 + 3;
		BtnClick.x2 = getx() + getwidth();
		gotoXY(_hScreen, BtnClick.x2, BtnClick.y2);
		std::cout << char(31);
	}

protected:
	struct
	{
		int x1, x2, y1, y2;
	}BtnClick;
	std::string _strTiltle;
	int selectedindex = -1;
	int posPrintInt = 0;
	int gxShow, gyShow;
	IList<_T>* _listObj;
	ACTIONBUTTON actionButton = nullptr;
};

#endif // !ListBox_H

