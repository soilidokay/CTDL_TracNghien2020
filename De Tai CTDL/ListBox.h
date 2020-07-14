#ifndef ListBox_H
#define ListBox_H

#include "Window.h"

template<class _T>
class ListBox : public window
{
public:
	ListBox(int width, int height, int x, int y) : window(width, height, x, y)
	{
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
	node<_T>* GetHightLight(int index) {
		if (index >= _listObj->getSize()) return NULL;
		node<_T>* tempPtr = _listObj->getfirst();
		for (; index > 0; index--)	tempPtr = tempPtr->next;
		return tempPtr;
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
			selected = GetHightLight(evt._Smouse.y - gety() - 4 + posPrintInt);
			if (selected != NULL) {
				showLObj();
				if (actionButton) {
					actionButton(evt);
				}
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
	void setchose(node<_T>* chose) {
		selected = chose;

	}
	void setActionButton(const ACTIONBUTTON& func) {
		actionButton = func;
	}
	void setposPrint(node<_T>* pos) {  }
	node<_T>* getPosPrint() { return posPrint; }
	void setListObj(List<_T>* listObj) {
		_listObj = listObj;
		//selected = posPrint = _listObj->getfirst();
		//showLObj();
		posPrintInt = 0;
	}
	node<_T>* getSelected() { return selected; }
	void showTitle() {
		TextColor(_hScreen, colorbk_darkblue | color_white);
		gotoXY(_hScreen, getx() + 1, gety() + 3);
		_T::settitle();
	}
	virtual void showLObj() {
		if (getheight() < 2 || _listObj->isempty()) return;
		int count = 0;
		_T* temp = NULL;
		node<_T>* TravNode = GetHightLight(posPrintInt);
		showTitle();
		TextColor(_hScreen, getcolor());
		std::cout << std::setfill(' ');

		int gy = gety() + 4;
		int gx = getx() + 1;
		while (count < getheight() - 3)
		{
			gotoXY(_hScreen, gx, gy + count++);
			if (TravNode != NULL) {
				if (TravNode == selected) {
					std::cout << std::setw(3) << posPrintInt + count; DrawHight(selected->info, count - 1);
				}
				else {
					std::cout << std::setw(3) << posPrintInt + count << char(179) << TravNode->info;
				}
				TravNode = TravNode->next;
			}
			else std::cout << std::setw(3) << posPrintInt + count << char(179) << temp;
		}

	}
	void addNode(_T* Dat) {
		if (_listObj->search(Dat) == NULL) {
			node<_T>* temp = _listObj->insertConst(Dat);
			setchose(temp);
			showLObj();
		}
	}
	_T* DelNode() {
		if (selected != NULL) {
			//temp = selected->info;
			_T* temp = selected->info;
			_listObj->DelCen(selected->info);
			showLObj();
			return temp;
		}
		return NULL;
	}
	void DrawHight(_T* Obj, int trav) {
		TextColor(_hScreen, colorbk_cyan | color_white);
		gotoXY(_hScreen, getx() + 4, gety() + 4 + trav);
		std::cout << char(179) << Obj;
		TextColor(_hScreen, getcolor());
	}
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
	node<_T>* selected;
	int posPrintInt = 0;
	List<_T>* _listObj;
	ACTIONBUTTON actionButton = nullptr;
};

#endif // !ListBox_H

