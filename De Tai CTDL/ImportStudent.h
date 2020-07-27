#ifndef ImportStudent_H
#define ImportStudent_H
#include "Form.h"

using namespace std;

class importStudent :public Form
{
public:
	importStudent(Form* Fbackup, int width, int height, int bkcolor) :
		Form(Fbackup, width, height, bkcolor)
	{
		constructor();
		setEventMouseOrKey();
		DrawToScreen();
	}
	void constructor()override {
		//Listbox lop


		//
		LBLopHoc = new CheckList<LopHoc>(78, 2, 6, Events);
		LBLopHoc->setheightLB(15);
		LBLopHoc->setColor(_bkcolor | color_grey);
		LBLopHoc->setStrTiltle("Danh sach lop hoc ");
		LBLopHoc->setGroupEle(false);
		LBLopHoc->setActionCollapse(bind(&importStudent::ActionListClass, this, _1));
		*Events += LBLopHoc;

		//
		LBStudent = new ListBox<Sinhvien>(82, 10, 0, 9);
		LBStudent->setColor(_bkcolor | color_grey);
		LBStudent->setStrTiltle("Danh sach sinh vien ");
		LBStudent->setActionItemClick(bind(&importStudent::ActionListStudent, this, _1));
		*Events += LBStudent;

		//lable Ma lop
		LIdStudent = new Label(10, 1, 0, 0);
		LIdStudent->settext(" Ma id");
		LIdStudent->setColor(colorbk_white | color_grey);
		//lable ten lop
		LlastName = new Label(10, 1, 37, 0);
		LlastName->settext("Ho");
		LlastName->setColor(colorbk_white | color_grey);
		//Lable password
		LPass = new Label(10, 1, 2, 3);
		LPass->settext("pass");
		LPass->setColor(colorbk_white | color_grey);
		//Lable ten
		Lfirst = new Label(10, 1, 37, 3);
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
		//-------Button Clear
		btnClear = new Button(6, 1, 15, 21);
		btnClear->setText("Moi");
		btnClear->setActionButton(bind(&importStudent::ActionClear, this, _1));
		*Events += btnClear;
		//-------Botton them
		btnAdd = new Button(6, 1, 24, 21);
		btnAdd->setText("Luu");
		btnAdd->setActionButton(bind(&importStudent::ActionAdd, this, _1));
		*Events += btnAdd;
		//-------Botton xoa
		btnDel = new Button(6, 1, 33, 21);
		btnDel->setText("Xoa");
		btnDel->setActionButton(bind(&importStudent::ActionDel, this, _1));
		*Events += btnDel;
		//-------Botton luu
		btnSave = new Button(6, 1, 42, 21);
		btnSave->setText("Sua");
		btnSave->setActionButton(bind(&importStudent::ActionSave, this, _1));
		*Events += btnSave;
		//-------Botton thoat
		btnExit = new Button(6, 1, 51, 21);
		btnExit->setText("Thoat");
		btnExit->setActionButton(bind(&importStudent::ActionExit, this, _1));
		*Events += btnExit;
		//--------labcheckbox
		LChckSex = new Label(6, 1, 71, 0);
		LChckSex->setColor(colorbk_white | color_grey);
		LChckSex->settext("NAM");
		//--------Check box
		chckBocSex = new checkbox(75, 0);
		chckBocSex->setColor(colorbk_white | color_blue);
		*Events += chckBocSex;
		//-----------------
		nObj = 17; Showobj = new window * [nObj];
		Showobj[0] = LBLopHoc;
		Showobj[1] = LBStudent;
		Showobj[2] = LIdStudent;
		Showobj[3] = LlastName;
		Showobj[4] = LPass;
		Showobj[5] = Lfirst;
		Showobj[6] = IPidStudent;
		Showobj[7] = IPlastname;
		Showobj[8] = IPpass;
		Showobj[9] = IPfirst;
		Showobj[10] = btnClear;
		Showobj[11] = btnAdd;
		Showobj[12] = btnDel;
		Showobj[13] = btnSave;
		Showobj[14] = btnExit;
		Showobj[15] = LChckSex;
		Showobj[16] = chckBocSex;
		ClassCurrent = NULL;
		setlists(_Context->LopHocs->ToArrayList(500));

	}

	bool conditionfiltersv(Sinhvien* sv, int index, LopHoc* lh) {
		return sv->getMaLop() == lh->getId();
	}

	bool forEachLop(LopHoc* lh, int index) {
		IList<Sinhvien>* temps = lstSinhVien->filter([&](Sinhvien* sv, int index) {return this->conditionfiltersv(sv, index, lh); });
		lh->setLSinhvien((List<Sinhvien>*)temps);
		return true;
	}

	void setlists(IList<LopHoc>* lstStu) {
		lstSinhVien = _Context->SinhViens->ToList();
		lstStu->forEach([&](LopHoc* lh, int index) {return this->forEachLop(lh, index); });
		LBLopHoc->setListObj(lstStu);
	}

private:

	bool conditionfilterstudent(Sinhvien* sv, int index) {
		return this->ClassCurrent->getId() == sv->getMaLop();
	}
	void ActionListStudent(EventConsole& evt) {
		Sinhvien* temp = LBStudent->getSelected();
		if (temp == NULL) return;
		IPidStudent->setText(temp->getId());
		IPlastname->setText(temp->getlastname());
		IPpass->setText(temp->getPass());
		IPfirst->setText(temp->getfirstname());
		chckBocSex->setChck(temp->getsex());
	}
	void ActionListClass(EventConsole& evt) {
		if (ClassCurrent != LBLopHoc->GetDataChecked()) {
			ClassCurrent = LBLopHoc->GetDataChecked();
			LBStudent->setListObj(ClassCurrent->getLSinhvien());
			LBStudent->showLObj();
		}
	}

	//void ShowWarning(std::string text) {
	//	warning war(70, 10, 5, colorbk_darkgreen | color_red);
	//	war.SetScreen(_hSCreen);
	//	war.setBtnCancel(0);
	//	war.settext(text);
	//	war.action(evt);
	//}

	//action button
	void ActionClear(EventConsole& evt) {
		IPidStudent->setText("");
		IPlastname->setText("");
		IPpass->setText("");
		IPfirst->setText("");
		chckBocSex->setChck(false);
	}
	void ActionAdd(EventConsole& evt) {
		if (ClassCurrent == NULL) {
			ShowWarning(_hSCreen, "ban chua chon lop hoc!!!");
			return;
		}

		if (IPidStudent->Gettext().length() > 0) {
			Sinhvien* temp = new Sinhvien(
				IPidStudent->Gettext(),
				IPlastname->Gettext(),
				IPfirst->Gettext(),
				chckBocSex->getChck(),
				IPpass->Gettext()
			);
			int index = lstSinhVien->Search(temp);
			if (index > -1) {
				ShowWarning(_hSCreen, "Sinh vien da ton tai!");
				return;
			}

			temp->SetMaLop(ClassCurrent->getId());
			LBStudent->addNode(temp);
			lstSinhVien->InsertConst(temp);
			_Context->SinhViens->Add(temp);
		}
	}
	void ActionDel(EventConsole& evt) {
		Sinhvien* temp = LBStudent->getSelected();
		if (temp != NULL) {
			_Context->SinhViens->Delete(temp);
			LBStudent->DelNode();
		}
	}
	void ActionSave(EventConsole& evt) {
		Sinhvien* temp = LBStudent->getSelected();

		if (temp == NULL) return;

		if (temp->getId() != IPidStudent->Gettext()) {
			ShowWarning(_hSCreen, "Sinh vien khong ton tai!");
			return;
		}


		temp->setlastname(IPlastname->Gettext());
		temp->setfirstname(IPfirst->Gettext());
		temp->setsex(chckBocSex->getChck());
		temp->SetPass(IPpass->Gettext());
		temp->SetMaLop(ClassCurrent->getId());
		LBStudent->showLObj();
		_Context->SinhViens->Update(temp);
	}
	void ActionExit(EventConsole& evt) {
		Close();
	}
private:
	ListBox<Sinhvien>* LBStudent;
	CheckList<LopHoc>* LBLopHoc;
	Label* LIdStudent, * LlastName, * LPass, * Lfirst, * LChckSex;
	InPutBox* IPidStudent, * IPlastname, * IPpass, * IPfirst;
	Button* btnClear, * btnAdd, * btnDel, * btnSave, * btnExit;
	checkbox* chckBocSex;
	IList<Sinhvien>* lstSinhVien;
	LopHoc* ClassCurrent;
};
#endif // !ImportStudent_H
