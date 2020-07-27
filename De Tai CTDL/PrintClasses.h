#ifndef PRINTCLASES_H
#define PRINTCLASES_H

#include "Form.h"

class PrintClasses : public Form
{
public:
	PrintClasses(Form* Fbackup, int width, int height, int bkcolor = colorbk_darkwhite) : Form(Fbackup, width, height, bkcolor) {
		constructor();
		setEventMouseOrKey();
		DrawToScreen();
	}
	void constructor() override {
		//label title
		_Title = new Label(30, 1, 30, 0);
		_Title->settext("Danh sach lop hoc");
		_Title->setColor(colorbk_yellow | color_red);
		//CheckList SchoolYear
		_CLSchoolYear = new CheckList<SchoolYear>(30, 25, 2, Events);
		_CLSchoolYear->setheightLB(15);
		_CLSchoolYear->setColor(_bkcolor | color_grey);
		_CLSchoolYear->setStrTiltle("Nien Khoa");
		_CLSchoolYear->setGroupEle(false);
		_CLSchoolYear->setActionCollapse(bind(&PrintClasses::ActionListSchoolYear, this, _1));
		*Events += _CLSchoolYear;
		//ListBox Class
		_LBClasses = new ListBox<LopHoc>(78, 40, 0, 6);
		_LBClasses->setColor(_bkcolor | color_grey);
		_LBClasses->setStrTiltle("Danh Sach Lop Hoc");
		_LBClasses->setActionItemClick(bind(&PrintClasses::ActionListClass, this, _1));
		*Events += _LBClasses;
		//btn exit
		
		BtnExit = new Button(6, 1, 60, 2);
		BtnExit->setText("Thoat");
		BtnExit->setActionButton(bind(&PrintClasses::actionExit, this, _1));
		*Events += BtnExit;


		nObj = 4; Showobj = new window * [nObj];
		Showobj[0] = _Title;
		Showobj[1] = _CLSchoolYear;
		Showobj[2] = _LBClasses;
		Showobj[3] = BtnExit;
		setlists(_Context->LopHocs->ToArrayList(500));
	}
private:
	void actionExit(EventConsole& evt) {
		Close();
	}

	void setlists(IList<LopHoc>* lstClass) {
		lstClass->RadixSort([&](LopHoc* lh) {return lh->getSchoolYear(); });
		List<SchoolYear>* lstSchool = new List<SchoolYear>;
		string temp = "-a";
		List<LopHoc>* lstLopHocTem = NULL;
		lstClass->forEach([&](LopHoc* lh, int index)
			{
				if (lh->getSchoolYear() != temp) {
					temp = lh->getSchoolYear();
					SchoolYear* data = new SchoolYear(lstSchool->getSize(),temp);
					lstSchool->insertlast(data);

					lstLopHocTem = new List<LopHoc>;
					lstLopHocTem->InsertConst(lh);

					data->setLstLopHop(lstLopHocTem);
				}
				else {
					lstLopHocTem->insertlast(lh);
				}
				return true;
			}
		);
		_CLSchoolYear->setListObj(lstSchool);

		//_LBClasses->setListObj(lstClass);
	}
	void ActionListSchoolYear(EventConsole& evt) {
		if (_SchoolYearCurrent != _CLSchoolYear->GetDataChecked()) {
			_SchoolYearCurrent = _CLSchoolYear->GetDataChecked();
			_LBClasses->setListObj(_SchoolYearCurrent->getLstLopHoc());
			_LBClasses->showLObj();
		}
	}
	void ActionListClass(EventConsole& evt) {

	}

	CheckList<SchoolYear>* _CLSchoolYear;
	ListBox<LopHoc>* _LBClasses;
	Label* _Title;
	SchoolYear* _SchoolYearCurrent = NULL;
	Button* BtnExit = NULL;
};

#ifndef PRINTCLASES_CPP
#include"PrintClasses.cpp"
#endif // !PRINTCLASES_CPP


#endif // !PRINTCLASES_H


