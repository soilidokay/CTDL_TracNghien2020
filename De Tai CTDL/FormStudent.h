#ifndef FORMSTUDENT_H
#define FORMSTUDENT_H

#include "ImportClass.h"
#include "ImportStudent.h"
#include "ImpObject.h"
#include "ImpQuestion.h"
#include "PrintClasses.h"
#include "ImportInfoTerm.h"

class FormStudent : public Form
{
public:
	FormStudent(Form* Fbackup, int width, int height, int bkcolor) :
		Form(Fbackup, width, height, bkcolor)
	{
		constructor();
		setEventMouseOrKey();
		DrawToScreen();
	}

	void constructor()override {

		//-----------------
		BtnTerm = new Button(48, 1, 1, 1);
		BtnTerm->setText("Nhap thong tin thi");
		BtnTerm->setActionButton(bind(&FormStudent::ActionBtnInfoTerm, this, _1));
		*Events += BtnTerm;
		//------------------
		BtnLogout = new Button(48, 1, 1, 5);
		BtnLogout->setText("Dang Xuat");
		BtnLogout->setActionButton(bind(&FormStudent::ActionBtnLogOut, this, _1));
		*Events += BtnLogout;
		//-------------------
		nObj = 2;
		Showobj = new window * [nObj];
		Showobj[0] = BtnTerm;
		Showobj[1] = BtnLogout;

		//--------------------
	}
	void SyncData() {

	}

	~FormStudent() {
	}
private:
	void ActionBtnInfoTerm(EventConsole& evt) {
		ImportInfoTerm * FormTerm = new ImportInfoTerm(this, 50, 25, colorbk_white);
		FormTerm->show();
	}
	void ActionBtnLogOut(EventConsole& evt) {
		Close();
	}
	Button* BtnTerm, * BtnLogout;
};

#endif // !FORMSTUDENT_H
