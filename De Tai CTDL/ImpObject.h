#ifndef ImpObject_H
#define ImpObject_H

#include "Form.h"

class ImpObject : public Form
{
public:
	ImpObject(Form *Fbackup, int width, int height, int bkcolor) : Form(Fbackup, width, height, bkcolor)
	{
		constructor();
		setEventMouseOrKey();
		DrawToScreen();
	}
	void constructor()override {
		//Listbox lop
		nObj = 9;
		//
		LBObject = new ListBox<Monhoc>(78, 10, 0, 8);
		LBObject->setColor(_bkcolor | color_grey);
		LBObject->setStrTiltle("Danh sach mon hoc ");
		LBObject->setActionButton(bind(&ImpObject::actionLBObj, this, _1));
		*Events += LBObject;
		//lable Ma lop
		LIdObject = new Lable(10, 1, 0, 3);
		LIdObject->settext(" Ma Mon");
		LIdObject->setColor(colorbk_white | color_grey);
		*Events += LIdObject;

		//lable ten lop
		LNameObject = new Lable(10, 1, 42, 3);
		LNameObject->settext("Ten Mon");
		LNameObject->setColor(colorbk_white | color_grey);
		//inputbox idclass
		IpIdObject = new InPutBox(25, 1, 10, 3);
		IpIdObject->setColor(colorbk_white | color_blue);
		*Events += IpIdObject;
		//inputbox nameclass
		IIPnameObject = new InPutBox(25, 1, 53, 3);
		IIPnameObject->setColor(colorbk_white | color_blue);
		*Events += IIPnameObject;
		//-------Botton them
		btnAdd = new Button(6, 1, 24, 20);
		btnAdd->setText("Moi");
		btnAdd->setActionButton(bind(&ImpObject::ActionAdd, this, _1));
		*Events += btnAdd;
		//-------Botton xoa
		btnDel = new Button(6, 1, 33, 20);
		btnDel->setText("Xoa");
		btnDel->setActionButton(bind(&ImpObject::ActionDel, this, _1));
		*Events += btnDel;
		//-------Botton luu
		btnSave = new Button(6, 1, 42, 20);
		btnSave->setText("Save");
		btnSave->setActionButton(bind(&ImpObject::ActionSave, this, _1));
		*Events += btnSave;
		//-------Botton thoat
		btnExit = new Button(6, 1, 51, 20);
		btnExit->setText("Thoat");
		btnExit->setActionButton(bind(&ImpObject::ActionExit, this, _1));
		*Events += btnExit;
		//-----------------

		Showobj = new window*[nObj];

		Showobj[0] = LBObject;
		Showobj[1] = LIdObject;
		Showobj[2] = LNameObject;
		Showobj[3] = IpIdObject;
		Showobj[4] = IIPnameObject;
		Showobj[5] = btnAdd;
		Showobj[6] = btnDel;
		Showobj[7] = btnSave;
		Showobj[8] = btnExit;

	}
	void setlists( List<Monhoc> * lstObj) {
		LBObject->setListObj(lstObj);
	}
	
private:

	//----------
	void actionLBObj(EventConsole & evt) {
		node<Monhoc>* temp = LBObject->getSelected();
		if (temp == NULL) return;
		IpIdObject->setText(temp->info->getId());
		IIPnameObject->setText(temp->info->getName());
	}

	//action button

	void ActionAdd(EventConsole& evt) {
		if (IpIdObject->Gettext().length() > 0) {
			Monhoc* temp = new Monhoc(IpIdObject->Gettext(),
				IIPnameObject->Gettext());
			LBObject->addNode(temp);
		}
	}	
	void ActionDel(EventConsole& evt) {
		LBObject->DelNode();
	}
	void ActionSave(EventConsole& evt) {
		node<Monhoc>* temp = LBObject->getSelected();
		if (temp == NULL)return;
		temp->info->setidobject(IpIdObject->Gettext());
		temp->info->setname(IIPnameObject->Gettext());
		LBObject->showLObj();
	}
	void ActionExit(EventConsole& evt) {
		Close();
	}
private:
	ListBox<Monhoc> *LBObject;
	Lable *LIdObject, *LNameObject;
	InPutBox * IpIdObject, *IIPnameObject;
	Button *btnAdd, *btnDel, *btnSave, *btnExit;
};
#endif // !ImpObject_H


