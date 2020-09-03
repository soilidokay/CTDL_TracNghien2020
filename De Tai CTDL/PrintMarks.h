#ifndef PRINTMARK_H
#define PRINTMARK_H
#include "Form.h"

class PrintMark : public Form
{
public:
	PrintMark(Form* Fbackup, int bkcolor = colorbk_white) : Form(Fbackup, 80, 60, bkcolor) {
		constructor();
		setEventMouseOrKey();
		DrawToScreen();
	}
	void constructor() override {
		//label title
		_Title = new Label(8, 1, 35, 0);
		_Title->settext("Ban Diem");
		_Title->setColor(colorbk_yellow | color_red);
		//CheckList Object
		_CLObject = new CheckList<Monhoc>(50, 15, 2, Events);
		_CLObject->setheightLB(15);
		_CLObject->setColor(_bkcolor | color_grey);
		_CLObject->setStrTiltle("Mon Hoc");
		_CLObject->setGroupEle(false);
		_CLObject->setActionCollapse(bind(&PrintMark::ActionListObject, this, _1));
		*Events += _CLObject;
		//CheckList Class
		_CLClasses = new CheckList<LopHoc>(70, 5, 6, Events);
		_CLClasses->setheightLB(15);
		_CLClasses->setColor(_bkcolor | color_grey);
		_CLClasses->setStrTiltle("Lop Hoc");
		_CLClasses->setGroupEle(false);
		_CLClasses->setActionCollapse(bind(&PrintMark::ActionListClasses, this, _1));
		*Events += _CLClasses;
		//ListBox Class
		_LBMarkStudent = new ListBox<ModelMarkSinhvien>(78, 45, 0, 10);
		_LBMarkStudent->setColor(_bkcolor | color_grey);
		_LBMarkStudent->setStrTiltle("Bang Diem Sinh vien");
		_LBMarkStudent->setActionItemClick(bind(&PrintMark::ActionListClass, this, _1));
		*Events += _LBMarkStudent;
		//btn exit

		BtnExit = new Button(6, 1, 70, 2);
		BtnExit->setText("Thoat");
		BtnExit->setActionButton(bind(&PrintMark::actionExit, this, _1));
		*Events += BtnExit;


		nObj = 5; Showobj = new window * [nObj];
		Showobj[0] = _Title;
		Showobj[1] = _CLObject;
		Showobj[2] = _CLClasses;
		Showobj[3] = _LBMarkStudent;
		Showobj[4] = BtnExit;
		setlists(_Context->LopHocs->ToArrayList(500));
	}
	~PrintMark() {
		_lstDiem->Clear(true);
		delete _lstDiem;
		lstSinhVien->Clear(true);
		delete lstSinhVien;
		lstMark->Clear(true);
		delete lstMark;
	}
private:
	void actionExit(EventConsole& evt) {
		Close();
	}
	bool conditionfiltersv(Sinhvien* sv, int index, LopHoc* lh) {
		return sv->getMaLop() == lh->getId();
	}

	bool forEachLop(LopHoc* lh, int index) {
		IList<Sinhvien>* temps = lstSinhVien->filter([&](Sinhvien* sv, int index) {return this->conditionfiltersv(sv, index, lh); });
		lh->setLSinhvien((List<Sinhvien>*)temps);
		return true;
	}
	void setlists(IList<LopHoc>* lstClass) {
		lstSinhVien = _Context->SinhViens->ToList();
		_lstDiem = _Context->Diems->ToList();
		lstClass->forEach([&](LopHoc* lh, int index) {return this->forEachLop(lh, index); });
		_CLClasses->setListObj(lstClass);
		_CLObject->setListObj(_Context->MonHocs->ToArrayList(300));
	}
	void ActionListObject(EventConsole& evt) {
		this->ShowListMarkStudent();
	}
	void ActionListClasses(EventConsole& evt) {
		this->ShowListMarkStudent();
	}
	void ShowListMarkStudent() {
		LopHoc* lop = _CLClasses->GetDataChecked();
		if (lop == NULL) {
			return;
		}
		Monhoc* mon = _CLObject->GetDataChecked();
		if (mon == NULL) {
			return;
		}

		IList<Sinhvien>* _lstTemp = lop->getLSinhvien();
		 lstMark = _LBMarkStudent->getListObj();

		if (lstMark != NULL) {
			lstMark->Clear();
			delete lstMark;
		}
		// create list temp have size equal for list SV on Class
		lstMark = new ArrayList<ModelMarkSinhvien>(_lstTemp->getSize());
		Diem diem;
		_lstTemp->forEach([&](Sinhvien* sv, int index) {
			// set properties for obj diem
			diem.setObjectId(mon->getId());
			diem.setStudentId(sv->getId());
			node<Diem>* d = _lstDiem->search(&diem);
			ModelMarkSinhvien* temp = new ModelMarkSinhvien();

			temp->setidstudent(sv->getId());
			temp->setfirstname(sv->getfirstname());
			temp->setlastname(sv->getlastname());
			// check SV have progress test Question
			if (d == NULL) {
				temp->setMark("Chua thi");
			}
			else {
				temp->setMark(to_string(d->info->getScores()));
			}

			lstMark->InsertConst(temp);

			return true;
			});
		_LBMarkStudent->setListObj(lstMark);
		_LBMarkStudent->showLObj();

	}
	void ActionListClass(EventConsole& evt) {

	}

	CheckList<LopHoc>* _CLClasses;
	CheckList<Monhoc>* _CLObject;
	ListBox<ModelMarkSinhvien>* _LBMarkStudent;
	List<Sinhvien>* lstSinhVien;
	List<Diem>* _lstDiem;
	Label* _Title;
	Button* BtnExit = NULL; 
	IList<ModelMarkSinhvien>* lstMark;
};
#endif // !INMARK_H
