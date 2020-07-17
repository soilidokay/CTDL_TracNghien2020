#ifndef ImportStudent_H
#define ImportStudent_H
#include "Form.h"

using namespace std;

class importStudent :public Form
{
public:
importStudent(Form *Fbackup, int width, int height, int bkcolor) :
Form(Fbackup, width, height, bkcolor)
{
	constructor();
	setEventMouseOrKey();
	DrawToScreen();
}
void constructor()override {
	//Listbox lop
	nObj = 15;
	Showobj = new window*[nObj];
	//
	/*LBObject = new CheckListMMonhoc>(78, 2, 6,Events);
	LBObject->setheightLB(15);
	LBObject->setColor(_bkcolor | color_grey);
	LBObject->setStrTiltle("Danh sach mon hoc ");
	LBObject->SetWarnStr("Ban muon huy dang ky mon nay ?");
	*Events += LBObject;*/
	//
	LBStudent = new ListBox<Sinhvien>(82, 10, 0, 9);
	LBStudent->setColor(_bkcolor | color_grey);
	LBStudent->setStrTiltle("Danh sach sinh vien ");
	LBStudent->setActionButton(bind(&importStudent::ActionListClass,this,_1));
	*Events += LBStudent;
	//lable Ma lop
	LIdStudent = new Lable(10, 1, 0, 0);
	LIdStudent->settext(" Ma id");
	LIdStudent->setColor(colorbk_white | color_grey);
	//lable ten lop
	LlastName = new Lable(10, 1, 37, 0);
	LlastName->settext("Ho");
	LlastName->setColor(colorbk_white | color_grey);
	//Lable password
	LPass = new Lable(10, 1, 2, 3);
	LPass->settext("pass");
	LPass->setColor(colorbk_white | color_grey);
	//Lable ten
	Lfirst = new Lable(10, 1, 37, 3);
	Lfirst->settext("Ten");
	Lfirst->setColor(colorbk_white | color_grey);
	//inputbox idclass
	IPidStudent = new InPutBox(25, 1, 10, 0);
	IPidStudent->setColor(colorbk_white | color_blue);
	*Events += IPidStudent;
	//inputbox nameclass
	IPlastname = new InPutBox(25, 1, 43, 0);
	IPlastname->setColor(colorbk_white | color_blue);
	*Events += IPlastname;
	//Inputbox pass
	IPpass = new InPutBox(25, 1, 10, 3);
	IPpass->setColor(colorbk_white | color_blue);
	*Events += IPpass;
	//inputbox ten
	IPfirst = new InPutBox(25, 1, 43, 3);
	IPfirst->setColor(colorbk_white | color_blue);
	*Events += IPfirst;
	//-------Botton them
	btnAdd = new Button(6, 1, 24, 21);
	btnAdd->setText("Moi");
	btnAdd->setActionButton(bind(&importStudent::ActionAdd, this, _1));
	*Events += btnAdd;
	//-------Botton xoa
	btnDel = new Button(6, 1, 33, 21);
	btnDel->setText("Xoa");
	btnDel->setActionButton(bind(&importStudent::ActionDel, this, _1));
	*Events += btnDel;
	//-------Botton luu
	btnSave = new Button(6, 1, 42, 21);
	btnSave->setText("Save");
	btnSave->setActionButton(bind(&importStudent::ActionSave, this, _1));
	*Events += btnSave;
	//-------Botton thoat
	btnExit = new Button(6, 1, 51, 21);
	btnExit->setText("Thoat");
	btnExit->setActionButton(bind(&importStudent::ActionExit, this, _1));
	*Events += btnExit;
	//--------labcheckbox
	LChckSex = new Lable(6,1,71, 0);
	LChckSex->setColor(colorbk_white | color_grey);
	LChckSex->settext("NAM");
	//--------Check box
	chckBocSex = new checkbox(75, 0);
	chckBocSex->setColor(colorbk_white | color_blue);
	*Events += chckBocSex;
	//-----------------

	Showobj[0] = LBStudent;
	Showobj[0] = LBStudent;
	Showobj[1] = LIdStudent;
	Showobj[2] = LlastName;
	Showobj[3] = LPass;
	Showobj[4] = Lfirst;
	Showobj[5] = IPidStudent;
	Showobj[6] = IPlastname;
	Showobj[7] = IPpass;
	Showobj[8] = IPfirst;
	Showobj[9] = btnAdd;
	Showobj[10] = btnDel;
	Showobj[11] = btnSave;
	Showobj[12] = btnExit;
	Showobj[13] = LChckSex;
	Showobj[14] = chckBocSex;

	setlists(_Context->SinhViens->ToList());
}
void setlists(IList<Sinhvien> * lstStu) {
	LBStudent->setListObj(lstStu);
}

private:


void ActionListClass(EventConsole& evt) {
	Sinhvien *temp = LBStudent->getSelected();
	if (temp == NULL) return;
	IPidStudent->setText(temp->getId());
	IPlastname->setText(temp->getlastname());
	//IPpass->setText(temp->info->)
	IPfirst->setText(temp->getfirstname());
	chckBocSex->setChck(temp->getsex());
}
//action button
void ActionAdd(EventConsole& evt) {
	if (IPidStudent->Gettext().length() > 0) {
		Sinhvien* temp = new Sinhvien(
			IPidStudent->Gettext(),
			IPlastname->Gettext(),
			IPfirst->Gettext(),
			chckBocSex->getChck(),
			IPpass->Gettext()
		);
		LBStudent->addNode(temp);
		_Context->SinhViens->Add(temp);
	}
}
void ActionDel(EventConsole& evt) {
	Sinhvien * temp = LBStudent->getSelected();
	if (temp != NULL) {
		_Context->SinhViens->Delete(temp);
		LBStudent->DelNode();
	}
}
void ActionSave(EventConsole& evt) {
	Sinhvien* temp = LBStudent->getSelected();
	if (temp == NULL) return;
	temp->setidstudent(IPidStudent->Gettext());
	temp->setlastname(IPlastname->Gettext());
	temp->setfirstname(IPfirst->Gettext());
	temp->setsex(chckBocSex->getChck());
	temp->SetPass(IPpass->Gettext());
	LBStudent->showLObj();
	_Context->SinhViens->Update(temp);
}
void ActionExit(EventConsole& evt) {
	Close();
}
private:
	ListBox<Sinhvien> *LBStudent;
	Lable *LIdStudent, *LlastName,*LPass,*Lfirst,*LChckSex;
	InPutBox * IPidStudent, *IPlastname,*IPpass,*IPfirst;
	Button *btnAdd, *btnDel, *btnSave, *btnExit;
	checkbox *chckBocSex;
};
#endif // !ImportStudent_H
