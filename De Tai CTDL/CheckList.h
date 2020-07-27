#ifndef CheckList_H
#define CheckList_H

#include "List.h"
#include "EventMouseOrKey.h"
#include "ListBox.h"

template<typename _T>
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
	void setActionCollapse(const ACTIONBUTTON& func) {
		actionCollapse = func;
	}
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
			int index = selectedindex > -1 ? selectedindex : Checked;
			DrawHight(index);
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
	void SetChecked(int index) {
		Checked = index;
		if (getheight() > 1) {
			showLObj();
		}
		else {
			_T* data = GetDataChecked();
			if (data != NULL) {
				ShowTitle(data, _T::getSizeTitle());
			}
			else {
				std::string temp = "";
				for (int i = 0; i < _T::getSizeTitle(); i++)
				{
					temp += " ";
				}
				ShowTitle(temp, _T::getSizeTitle());
				ShowTitle(_strTiltle, _strTiltle.length());
			}
		}
	}
	List<_T>* GetListChecked() { return ListChecked; }
	void setStrTiltle(std::string strTiltle)override {
		_strTiltle = strTiltle;
		_strTiltle += 31;
	}
	CHAR_INFO* showlist() {
		if (getheight() > 1 || _listObj == NULL) return NULL;
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
	bool IsOpen() {
		return getheight() > 1;
	}
	virtual void backup(CHAR_INFO* charac) {
		if (IsOpen()) {
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
		/*warning Warn(70, 10, 5, colorbk_darkgreen | color_red);
		Warn.SetScreen(_hScreen);
		Warn.settext(_warnStr);
		Warn.action(evt);*/
		return ShowWarning(_hScreen, _warnStr, true);
	}
	void Actionchecks(EventConsole& evt) {
		if (evt._Smouse.x > getx() && evt._Smouse.x < getx() + 4 &&
			evt._Smouse.y > gety() + 1 && ListChecked != NULL) {

			_T* temp = _listObj->GetData(selectedindex);

			if (ListChecked->search(temp) != NULL) {
				if (ActionWarn(evt)) ListChecked->DelCen(temp);
				DrawCheckIndex(selectedindex);
			}
			else {
				ListChecked->insertConst(temp);
				DrawCheckIndex(selectedindex, colorbk_red | color_blue);
			}

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
			if (actionCollapse) {
				actionCollapse(evt);
			}
			_T* data = GetDataChecked();
			if (data != NULL) {
				ShowTitle(data, _T::getSizeTitle());
			}
			else {
				std::string temp = "";
				for (int i = 0; i < _T::getSizeTitle(); i++)
				{
					temp += " ";
				}
				ShowTitle(temp, _T::getSizeTitle());
				ShowTitle(_strTiltle, _strTiltle.length());
			}
			return;
		}
		else if (BclickBtn(evt) == 1) {
			if (_listObj == NULL) return;
			MoveUp(getSizeDisplay());
			showLObj();
		}
		else if (BclickBtn(evt) == 2) {
			if (_listObj == NULL) return;
			MoveDw(getSizeDisplay());
			showLObj();
		}
		else
		{
			if (_listObj == NULL) return;

			int SelectedIndexTemp = evt._Smouse.y - gety() - 4 + posPrintInt;
			if (SelectedIndexTemp > -1 && SelectedIndexTemp < _listObj->getSize()) {
				DrawHight(selectedindex);
				DrawHight(SelectedIndexTemp, colorbk_cyan | color_white);
				if (groupElement) Actionchecks(evt);
				else {
					DrawCheckIndex(selectedindex);
					DrawCheckIndex(SelectedIndexTemp, colorbk_red | color_blue);
					Checked = SelectedIndexTemp;
				}

				selectedindex = SelectedIndexTemp;

				if (actionButton) {
					actionButton(evt);
				}
			}

		}

		//_select = 1;
	}

	void DrawCheckIndex(int index, int color = -1) {
		if (index < 0 || index < posPrintInt || index >= getSizeDisplay() + posPrintInt) return;
		if (color < 0) color = getcolor();

		gotoXY(_hScreen, gxShow, gyShow + index - posPrintInt);

		TextColor(_hScreen, color);
		std::cout << setw(3) << index;
		TextColor(_hScreen, getcolor());
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
	ACTIONBUTTON actionCollapse = nullptr;
};

#endif // !CheckList_H
