#ifndef Formteach_H
#define Formteach_H
#include "ImportClass.h"
#include "ImportStudent.h"
#include "ImpObject.h"
#include "ImpQuestion.h"

class FormTeach : public Form
{
public:
	FormTeach(Form *Fbackup, int width, int height, int bkcolor) :
		Form(Fbackup, width, height, bkcolor)
	{
		constructor();
		setEventMouseOrKey();
		DrawToScreen();
	}
	
	void constructor()override {
		nObj = 4;
		Showobj = new window*[nObj];
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

		Showobj[0] = BtnImCl;
		Showobj[1] = BtnImpStu;
		Showobj[2] = BtnImpObj;
		Showobj[3] = BtnImpQue;

		//--------------------
		lstObj = new List<Monhoc>;
		Lstudent = new List<Sinhvien>;
		lstClass = new List<LopHoc>;
	}
	void SyncData() {
		
	}
	
	~FormTeach() {
	}
private:
	void ActionBtnImCl(EventConsole &evt) {
		importClass* Impclass = new importClass(this, 85, 25, colorbk_white);
		Impclass->setlists(Lstudent, lstClass);
		Impclass->show();
	}
	void ActionBtnImpStu(EventConsole &evt) {
		importStudent* ImpStu =new importStudent(this, 85, 25, colorbk_white);
		ImpStu->setlists(Lstudent, lstObj);
		ImpStu->show();
	}
	void ActionBtnImpQue(EventConsole &evt) {
		ImpQuestion* ImpQue = new ImpQuestion(this, 90, 30, colorbk_white);
		ImpQue->setList(lstObj);
		ImpQue->show();
	}
	void ActionBtnImpObj(EventConsole &evt) {
		ImpObject* impObject = new ImpObject(this, 80, 25, colorbk_white);
		impObject->setlists(lstObj);
		impObject->show();
	}
private:
	List<Monhoc> *lstObj;
	List<Sinhvien> *Lstudent;
	List<LopHoc> * lstClass;
	Button *BtnImCl, *BtnImpStu, *BtnImpQue, *BtnImpObj;
};
#endif // !Formteach_H
