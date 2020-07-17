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

	bool showSingle(_T* data, int index) override {
		gotoXY(_hScreen, gxShow, gyShow + index - posPrintInt);

		if ((groupElement
			&& ListChecked != NULL && ListChecked->search(data) != NULL) || Checked == index)
		{
			TextColor(_hScreen, colorbk_red | color_blue);
		}
		else {
			TextColor(_hScreen, getcolor());
		}

		std::cout << std::setw(3) << index;

		if (index == selectedindex || Checked == index) {
			DrawHight(selectedindex);
		}
		else {
			TextColor(_hScreen, getcolor());
			std::cout << char(179) << data;
		}

		return true;
	}
	/*virtual void showLObj() override {
		if (getheight() < 2 || _listObj->isempty()) return;
		int count = 0;
		_T* temp = NULL;
		node<_T>* TravNode = GetHightLight(posPrintInt);
		showTitle();
		TextColor(_hScreen, getcolor());
		std::cout << std::setfill(' ');
		_listObj->forEach(showSingle, posPrintInt, posPrintInt + getheight() - 4);
	}*/
	_T* GetDataChecked() { return _listObj->GetData(Checked); }
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

			_T* temp = _listObj->GetData(selectedindex);

			if (ListChecked->search(temp) != NULL) {
				if (ActionWarn(evt)) ListChecked->DelCen(temp);
			}
			else ListChecked->insertConst(temp);

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
			selectedindex = evt._Smouse.y - gety() - 4 + posPrintInt;
			if (selectedindex > -1) {
				if (groupElement) Actionchecks(evt);
				else {
					Checked = selectedindex;
				}
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
	int Checked = -1;
	int _heightLB;
	EventMouseOrKey* _containerEvent;
	std::string _warnStr;
	node<_T>* tempPtr;
};

#endif // !CheckList_H
