#pragma once
#include "Form.h"

class importStudent :public Form
{
public:
	typedef void (importStudent::*ACTION)(EventConsole&);
	importStudent(Form *Fbackup, int width, int height, int bkcolor) : Form(Fbackup, width, height, bkcolor)
	{
		constructor();
		setEventMouseOrKey();
	}
	void constructor()override {
		//Listbox lop
		nObj = 10;
		ArrayFunc = new ACTION[nObj];
		initAction();
		//
		LBObject = new ListBox(78, 1, 0, 4);
		LBObject->setheightLB(15);
		LBObject->setColor(_bkcolor | color_grey);
		LBObject->setStrTiltle("Danh sach sinh mon hoc ");
		ArrayFunc[0] = &importStudent::actioncheckbox;
		//
		LBStudent = new ListBox(78, 10, 0, 8);
		LBStudent->setColor(_bkcolor | color_grey);
		LBStudent->setStrTiltle("Danh sach sinh vien ");
		ArrayFunc[1] = &importStudent::ActionListClass;
		//lable Ma lop
		LIdStudent = new Lable(10, 1, 0, 0);
		LIdStudent->settext(" Ma id");
		LIdStudent->setColor(colorbk_white | color_grey);
		//lable ten lop
		LlastName = new Lable(10, 1, 42, 0);
		LlastName->settext("Ho");
		LlastName->setColor(colorbk_white | color_grey);
		//inputbox idclass
		IPidStudent = new InPutBox(25, 1, 10, 0);
		IPidStudent->setColor(colorbk_white | color_blue);
		//inputbox nameclass
		IPlastname = new InPutBox(25, 1, 53, 0);
		IPlastname->setColor(colorbk_white | color_blue);
		//-------Botton them
		btnAdd = new Button(6, 1, 24, 20);
		btnAdd->setText("Them");
		ArrayFunc[6] = &importStudent::ActionAdd;
		//-------Botton xoa
		btnDel = new Button(6, 1, 33, 20);
		btnDel->setText("Xoa");
		ArrayFunc[7] = &importStudent::ActionAdd;
		//-------Botton luu
		btnSave = new Button(6, 1, 42, 20);
		btnSave->setText("Save");
		ArrayFunc[8] = &importStudent::ActionAdd;
		//-------Botton thoat
		btnExit = new Button(6, 1, 51, 20);
		btnExit->setText("Thoat");
		ArrayFunc[9] = &importStudent::ActionAdd;
		//-----------------

		Showobj = new window*[nObj];

		Showobj[0] = LBObject;
		Showobj[1] = LBStudent;
		Showobj[2] = LIdStudent;
		Showobj[3] = LlastName;
		Showobj[4] = IPidStudent;
		Showobj[5] = IPlastname;
		Showobj[6] = btnAdd;
		Showobj[7] = btnDel;
		Showobj[8] = btnSave;
		Showobj[9] = btnExit;
	}
	void ActionImPort() {
		evt.KeyOrMouse = 0;
		evt.reset();
		int selec = 3;
		while (evt._key != 27)
		{
			if (selec > -1) {
				Showobj[selec]->action(evt);
				//thuc hien action ngoai
				if (Showobj[selec]->getselect() == 1) {
					Showobj[selec]->setselect(-1);
					if (this->ArrayFunc != NULL)
						(this->*ArrayFunc[selec])(evt);
				}
			}
			else KeyMouse(&evt);
			//su ly chuot hoac phim
			if (evt.KeyOrMouse) {
				selec = _area[evt._Smouse.y][evt._Smouse.x];
			}
			else
			{
				switch (evt._key)
				{
					//case key_Enter: selec = 4; break;
				default:
					selec = getCirNum(4, 5, selec); break;
				}
			}
		}
	}
private:
	void initAction() {
		for (int i = 0; i < nObj; i++) this->ArrayFunc[i] = NULL;
	}
	void actioncheckbox(EventConsole& evt) {
		CHAR_INFO* charac = LBObject->showlist();
		LBObject->setcheck(6);
		do
		{
			KeyMouse(&evt);
			if (LBObject->BclickBtn(evt));
		} while (LBObject->_checkmoue(evt) && evt._key != 27);
		LBObject->backup(charac);

	}
	void ActionListClass(EventConsole& evt) {
		LBStudent->setcheck(6);
		do
		{
			if (LBStudent->BclickBtn(evt));
			KeyMouse(&evt);
		} while (LBStudent->_checkmoue(evt) && evt._key != 27);
	}
	//action button
	void ActionAdd(EventConsole& evt) {
		KeyMouse(&evt);
	}
	void ActionDel(EventConsole& evt) {
		KeyMouse(&evt);
	}
	void ActionSave(EventConsole& evt) {
		KeyMouse(&evt);
	}
	void ActionExit(EventConsole& evt) {
		KeyMouse(&evt);
	}
private:
	ListBox *LBObject, *LBStudent;
	Lable *LIdStudent, *LlastName;
	InPutBox * IPidStudent, *IPlastname;
	ACTION *ArrayFunc;
	Button *btnAdd, *btnDel, *btnSave, *btnExit;
};
