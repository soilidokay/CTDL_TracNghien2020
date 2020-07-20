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
		_Title = new Lable(30, 1, 30, 0);
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

		nObj = 3; Showobj = new window * [nObj];
		Showobj[0] = _Title;
		Showobj[1] = _CLSchoolYear;
		Showobj[2] = _LBClasses;
		setlists(_Context->LopHocs->ToList());
	}
private:
	void setlists(IList<LopHoc>* lstClass) {
		_LBClasses->setListObj(lstClass);
	}
	void ActionListSchoolYear(EventConsole& evt) {

	}
	void ActionListClass(EventConsole& evt) {

	}

	CheckList<SchoolYear>* _CLSchoolYear;
	ListBox<LopHoc>* _LBClasses;
	Lable* _Title;
};

#ifndef PRINTCLASES_CPP
#include"PrintClasses.cpp"
#endif // !PRINTCLASES_CPP


#endif // !PRINTCLASES_H


