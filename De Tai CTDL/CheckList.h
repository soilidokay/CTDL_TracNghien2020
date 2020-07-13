#ifndef CheckList_H
#define CheckList_H

#include "List.h"
#include "ListBox.h"
#include "EventMouseOrKey.h"

template<class _T>
class CheckList : public ListBox<_T>
{
public:
	CheckList(int width, int x, int y, EventMouseOrKey* container) : ListBox<_T>(width, 1, x, y) {
		ListChecked = NULL;
		groupElement = 1;
		_containerEvent = container;
	}
	void setGroupEle(bool grElement) { groupElement = grElement; }
	void SetWarnStr(std::string wrnStr) { _warnStr = wrnStr; }
	void showLObj() override {
		if (getheight() < 3 || _listObj->isempty()) return;//

		int count = 0, trav = -1;
		_T* temp = NULL;
		node<_T>* TravNode = GetHightLight(posPrintInt);
		showTitle();
		std::cout << std::setfill(' ');
		TextColor(_hScreen, getcolor());

		int gy = gety() + 4;
		int gx = getx() + 1;
		while (count < getheight() - 3)
		{
			gotoXY(_hScreen, gx, gy + count);
			if (TravNode != NULL) {


				if (groupElement) {
					if (ListChecked != NULL && ListChecked->search(TravNode->info) != NULL)
						TextColor(_hScreen, colorbk_red | color_blue);
				}
				else if (selected != NULL && selected->info == TravNode->info)
					TextColor(_hScreen, colorbk_red | color_blue);

				std::cout << std::setw(3) << posPrintInt + count;

				if (TravNode == selected) {
					DrawHight(selected->info, count);
				}
				else {
					TextColor(_hScreen, getcolor());
					std::cout << char(179) << TravNode->info;
				}
				TravNode = TravNode->next;
			}
			else std::cout << std::setw(3) << posPrintInt + count << char(179) << temp;
			++count;
		}


	}
	void SetListCheck(List<_T>* Lst) { ListChecked = Lst; }
	List<_T>* GetListChecked() { return ListChecked; }
	void setStrTiltle(std::string strTiltle)override {
		_strTiltle = strTiltle;
		_strTiltle += 31;
	}
	CHAR_INFO* showlist() {
		if (getheight() > 1) return NULL;
		setheight(_heightLB);
		//sety(gety() - 9);
		SHORT height = getheight() + 3;
		SHORT width = getwidth() + 3;
		SHORT x = getx();
		SHORT y = gety();
		CHAR_INFO* charac = new CHAR_INFO[height * width];
		scl::ReadBlockChar(_hScreen, charac, height, width, x, y);
		show();
		setUpBtn(getcolor());
		setDwBtn(getcolor());
		return charac;
	}
	virtual void backup(CHAR_INFO* charac) {
		if (getheight() > 1) {
			SHORT height = getheight() + 3;
			SHORT width = getwidth() + 3;
			SHORT x = getx();
			SHORT y = gety();
			scl::WriteBlockChar(_hScreen, charac, height, width, x, y);
			setheight(1);
			//sety(gety() + 9);
		}
	}
	bool ActionWarn(EventConsole& evt) {
		warning Warn(70, 10, 5, colorbk_darkgreen | color_red);
		Warn.SetScreen(_hScreen);
		Warn.settext(_warnStr);
		Warn.action(evt);
		return Warn.GetOK();
	}
	void Actionchecks(EventConsole& evt) {
		if (evt._Smouse.x > getx() && evt._Smouse.x < getx() + 4 &&
			evt._Smouse.y > gety() + 1 && ListChecked != NULL) {
			if (ListChecked->search(selected->info) != NULL) {

				if (ActionWarn(evt)) ListChecked->DelNode(selected);
			}
			else ListChecked->insertConst(selected->info);
		}
	}
	//void action(EventConsole& evt)override {
	//	CHAR_INFO* charac = showlist();
	//	node<_T>* tempPtr = NULL;
	//	do
	//	{
	//		showLObj();
	//		KeyMouse(&evt);
	//		if (BclickBtn(evt) == 1) {
	//			tempPtr = MoveUp(posPrint, getheight() - 1);
	//			if (tempPtr != NULL) posPrint = tempPtr;
	//		}
	//		else if (BclickBtn(evt) == 2) {
	//			tempPtr = MoveDw(posPrint, getheight() - 1);
	//			if (tempPtr != NULL) posPrint = tempPtr;
	//		}
	//		else
	//		{
	//			tempPtr = Move(evt._Smouse.y);
	//			if (tempPtr != NULL) {
	//				selected = tempPtr;
	//				if (groupElement) Actionchecks(evt);
	//			}
	//		}
	//	} while (_checkmoue(evt) && evt._key != 27);
	//	backup(charac);
	//	//_select = 1;
	//}
	void action(EventConsole& evt)override {
		if (!evt.isMouseEvent()) {
			return;
		}
		if (!_containerEvent->isLock()) {
			_containerEvent->lockControl(this);
			charac = showlist();
			tempPtr = NULL;
			showLObj();
			scl::ShowCur(false);
		}
		else if (!this->_checkmoue(evt)) {
			_containerEvent->unLockControl(this);
			backup(charac);
			return;
		}

		if (BclickBtn(evt) == 1) {
			MoveUp(getheight() - 3);
		}
		else if (BclickBtn(evt) == 2) {
			MoveDw(getheight() - 3);
		}
		else
		{
			tempPtr = GetHightLight(evt._Smouse.y - gety() - 4 + posPrintInt);
			if (tempPtr != NULL) {
				selected = tempPtr;
				if (groupElement) Actionchecks(evt);
			}
		}
		showLObj();

		//_select = 1;
	}
	void setheightLB(int height) { _heightLB = height; }
private:
	CHAR_INFO* charac;
	bool groupElement;
	List<_T>* ListChecked;
	int _heightLB;
	EventMouseOrKey* _containerEvent;
	std::string _warnStr;
	node<_T>* tempPtr;
};

#endif // !CheckList_H
