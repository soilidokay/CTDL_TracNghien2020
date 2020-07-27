#ifndef Formteach_H
#define Formteach_H
#include "ImportClass.h"
#include "ImportStudent.h"
#include "ImpObject.h"
#include "ImpQuestion.h"
#include "PrintClasses.h"
#include "PrintMarks.h"
#include "DetailQuestion.h"

class FormTeach : public Form
{
public:
	FormTeach(Form* Fbackup, int bkcolor) :
		Form(Fbackup, 52, 35, bkcolor)
	{
		constructor();
		setEventMouseOrKey();
		DrawToScreen();
	}

	void constructor()override {

		//-----------------
		BtnImCl = new Button(48, 1, 1, 1);
		BtnImCl->setText("Nhap them lop");
		BtnImCl->setActionButton(bind(&FormTeach::ActionBtnImCl, this, _1));
		*Events += BtnImCl;
		//------------------
		BtnImpStu = new Button(48, 1, 1, 5);
		BtnImpStu->setText("Nhap them sinh vien");
		BtnImpStu->setActionButton(bind(&FormTeach::ActionBtnImpStu, this, _1));
		*Events += BtnImpStu;
		//-------------------
		BtnImpObj = new Button(48, 1, 1, 9);
		BtnImpObj->setText("Nhap Them mon hoc");
		BtnImpObj->setActionButton(bind(&FormTeach::ActionBtnImpObj, this, _1));
		*Events += BtnImpObj;
		//---------------------
		BtnImpQue = new Button(48, 1, 1, 13);
		BtnImpQue->setText("Nhap them cau hoi");
		BtnImpQue->setActionButton(bind(&FormTeach::ActionBtnImpQue, this, _1));
		*Events += BtnImpQue;
		//-------------------
		BtnPrintClass = new Button(48, 1, 1, 17);
		BtnPrintClass->setText("Danh sach lop hoc");
		BtnPrintClass->setActionButton(bind(&FormTeach::ActionBtnPrintCLass, this, _1));
		*Events += BtnPrintClass;
		//-------------------
		BtnPrintMarkStudent = new Button(48, 1, 1, 21);
		BtnPrintMarkStudent->setText("Bang Diem sinh vien");
		BtnPrintMarkStudent->setActionButton(bind(&FormTeach::ActionBtnMarkStudent, this, _1));
		*Events += BtnPrintMarkStudent;
		//-------------------
		btnPrintDetailQuestion = new Button(48, 1, 1, 25);
		btnPrintDetailQuestion->setText("Chi tiet bai thi");
		btnPrintDetailQuestion->setActionButton(bind(&FormTeach::ActionBtnPrintDetailQuestion, this, _1));
		*Events += btnPrintDetailQuestion;
		//-------------------

		BtnLogout = new Button(48, 1, 1, 29);
		BtnLogout->setText("Dang Xuat");
		BtnLogout->setActionButton(bind(&FormTeach::ActionBtnLogOut, this, _1));
		*Events += BtnLogout;
		//-------------------
		nObj = 8;
		Showobj = new window * [nObj];
		Showobj[0] = BtnImCl;
		Showobj[1] = BtnImpStu;
		Showobj[2] = BtnImpObj;
		Showobj[3] = BtnImpQue;
		Showobj[4] = BtnPrintClass;
		Showobj[5] = BtnPrintMarkStudent;
		Showobj[6] = btnPrintDetailQuestion;
		Showobj[7] = BtnLogout;

		//--------------------
	}
	void SyncData() {

	}

	~FormTeach() {
	}
private:
	void ActionBtnImCl(EventConsole& evt) {
		importClass* Impclass = new importClass(this, 85, 35, colorbk_white);
		Impclass->show();
	}
	void ActionBtnImpStu(EventConsole& evt) {
		importStudent* ImpStu = new importStudent(this, 85, 35, colorbk_white);
		ImpStu->show();
	}
	void ActionBtnImpQue(EventConsole& evt) {
		ImpQuestion* ImpQue = new ImpQuestion(this, 90, 60, colorbk_white);
		ImpQue->show();
	}
	void ActionBtnImpObj(EventConsole& evt) {
		ImpObject* impObject = new ImpObject(this, 80, 35, colorbk_white);
		impObject->show();
	}
	void ActionBtnPrintCLass(EventConsole& evt) {
		PrintClasses* PrintClass = new PrintClasses(this, 80, 50, colorbk_white);
		PrintClass->show();
	}
	void ActionBtnMarkStudent(EventConsole& evt) {
		PrintMark* Printmark = new PrintMark(this);
		Printmark->show();
	}
	void ActionBtnPrintDetailQuestion(EventConsole& evt) {
		DetailQuestion* form = new DetailQuestion(this);
		form->show();
	}
	void ActionBtnLogOut(EventConsole& evt) {
		Close();
	}
private:
	Button* BtnImCl, * BtnImpStu, * BtnImpQue,
		* BtnImpObj, * BtnPrintClass,
		* BtnPrintMarkStudent, * BtnLogout,
		* btnPrintDetailQuestion;
};
#endif // !Formteach_H
