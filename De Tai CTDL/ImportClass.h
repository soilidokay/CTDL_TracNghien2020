#ifndef ImportClass_H
#define ImportClass_H
#include"Form.h"

using namespace std;

class importClass :public Form
{
public:
	importClass(Form* Fbackup, int width, int height, int bkcolor) : Form(Fbackup, width, height, bkcolor)
	{
		constructor();
		setEventMouseOrKey();
		DrawToScreen();
	}
	void constructor()override {
		//Listbox lop
		//
		LBclass = new ListBox<LopHoc>(78, 10, 2, 8);
		LBclass->setColor(_bkcolor | color_grey);
		LBclass->setStrTiltle("Danh sach lop ");
		LBclass->setActionButton(bind(&importClass::actionListBox, this, _1));
		*Events += LBclass;
		//lable Ma lop
		LIdClass = new Lable(10, 1, 0, 0);
		LIdClass->settext(" Ma lop");
		LIdClass->setColor(colorbk_white | color_grey);
		//lable ten lop
		LNameClass = new Lable(10, 1, 42, 0);
		LNameClass->settext("Ten lop");
		LNameClass->setColor(colorbk_white | color_grey);
		//inputbox idclass
		IPidclass = new InPutBox(25, 1, 10, 0);
		IPidclass->setColor(colorbk_white | color_blue);
		*Events += IPidclass;
		//inputbox nameclass
		IPnameclass = new InPutBox(25, 1, 53, 0);
		IPnameclass->setColor(colorbk_white | color_blue);
		*Events += IPnameclass;
		//-------Button Clear
		btnClear = new Button(6, 1, 15, 20);
		btnClear->setText("Moi");
		btnClear->setActionButton(bind(&importClass::ActionClear, this, _1));
		*Events += btnClear;
		//-------Botton them
		btnAdd = new Button(6, 1, 24, 20);
		btnAdd->setText("Luu");
		btnAdd->setActionButton(bind(&importClass::ActionAdd, this, _1));
		*Events += btnAdd;
		//-------Botton xoa
		btnDel = new Button(6, 1, 33, 20);
		btnDel->setText("Xoa");
		btnDel->setActionButton(bind(&importClass::ActionDel, this, _1));
		*Events += btnDel;
		//-------Botton luu
		btnSave = new Button(6, 1, 42, 20);
		btnSave->setText("Sua");
		btnSave->setActionButton(bind(&importClass::ActionSave, this, _1));
		*Events += btnSave;
		//-------Botton thoat
		btnExit = new Button(6, 1, 51, 20);
		btnExit->setText("Thoat");
		btnExit->setActionButton(bind(&importClass::ActionExit, this, _1));
		*Events += btnExit;

		nObj = 10;
		Showobj = new window * [nObj];

		Showobj[0] = LBclass;
		Showobj[1] = LIdClass;
		Showobj[2] = LNameClass;
		Showobj[3] = IPidclass;
		Showobj[4] = IPnameclass;
		Showobj[5] = btnClear;
		Showobj[6] = btnAdd;
		Showobj[7] = btnDel;
		Showobj[8] = btnSave;
		Showobj[9] = btnExit;

		setlists(_Context->LopHocs->ToArrayList(500));
	}
	void setlists( IList<LopHoc>* lstClass) {
		LBclass->setListObj(lstClass);
	}

private:

	void actionListBox(EventConsole& evt) {
		LopHoc* lh = LBclass->getSelected();
		if (lh == NULL) return;
		IPidclass->setText(lh->getId());
		IPnameclass->setText(lh->getName());
	}
	//action button
	void ActionClear(EventConsole& evt) {
		IPidclass->setText("");
		IPnameclass->setText("");
	}
	void ActionAdd(EventConsole& evt) {
		if (IPidclass->Gettext().length() > 0) {
			LopHoc* temp = new LopHoc(IPidclass->Gettext(),
				IPnameclass->Gettext());
			LBclass->addNode(temp);
			_Context->LopHocs->Add(temp);
		}
	}
	void ActionDel(EventConsole& evt) {
		LopHoc* lh = LBclass->getSelected();
		if (lh != NULL) {
			_Context->LopHocs->Delete(lh);
			LBclass->DelNode();
		}
	}
	void ActionSave(EventConsole& evt) {
		LopHoc* lh = LBclass->getSelected();
		if (lh == NULL) return;

		if (lh->getId() != IPidclass->Gettext()) {
			ShowWarning(_hSCreen,"Lop hoc khong ton tai!");
			return;
		};

		lh->setnameclass(IPnameclass->Gettext());

		LBclass->showLObj();
		_Context->LopHocs->Update(lh);
	}
	void ActionExit(EventConsole& evt) {
		Close();
	}
private:
	ListBox<LopHoc>* LBclass;
	Lable* LIdClass, * LNameClass;
	InPutBox* IPidclass, * IPnameclass;
	Button* btnClear,* btnAdd, * btnDel, * btnSave, * btnExit;
};
#endif // !ImportClass_H

