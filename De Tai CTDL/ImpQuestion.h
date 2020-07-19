#ifndef Question_H
#define Question_H

#include "Form.h"

class ImpQuestion : public Form
{
public:
	ImpQuestion(Form* Fbackup, int width, int height, int bkcolor) :
		Form(Fbackup, width, height, bkcolor)
	{
		constructor();
		setEventMouseOrKey();
		DrawToScreen();
	}
	void setList(List<Monhoc>* listObj) {
		CLObject->setListObj(listObj);
	}
	void constructor()override {
		//
		CLObject = new CheckList<Monhoc>(76, 12, 1, Events);
		CLObject->setColor(_bkcolor | color_grey);
		CLObject->setheightLB(15);
		CLObject->setStrTiltle("Danh sach mon hoc");
		CLObject->setGroupEle(false);
		CLObject->setActionCollapse(bind(&ImpQuestion::ActionListQuestion, this, _1));
		*Events += CLObject;
		//
		Lquest = new Lable(10, 1, 0, 4);
		Lquest->settext("Cau hoi");
		Lquest->setColor(colorbk_white | color_grey);
		//
		LanswerA = new Lable(10, 1, 0, 7);
		LanswerA->settext("Dap an A");
		LanswerA->setColor(colorbk_white | color_grey);
		//
		LanswerB = new Lable(10, 1, 0, 10);
		LanswerB->settext("Dap an B");
		LanswerB->setColor(colorbk_white | color_grey);
		//
		LanswerC = new Lable(10, 1, 0, 13);
		LanswerC->settext("Dap an C");
		LanswerC->setColor(colorbk_white | color_grey);
		//
		LanswerD = new Lable(10, 1, 0, 16);
		LanswerD->settext("Dap an D");
		LanswerD->setColor(colorbk_white | color_grey);
		//
		Lanswer = new Lable(10, 1, 0, 19);
		Lanswer->settext("Dap An");
		Lanswer->setColor(colorbk_white | color_grey);
		//
		IPquest = new InPutBox(76, 1, 12, 4);
		IPquest->setColor(colorbk_white | color_blue);
		*Events += IPquest;
		//
		IPanswerA = new InPutBox(76, 1, 12, 7);
		IPanswerA->setColor(colorbk_white | color_blue);
		*Events += IPanswerA;
		//
		IPanswerB = new InPutBox(76, 1, 12, 10);
		IPanswerB->setColor(colorbk_white | color_blue);
		*Events += IPanswerB;
		//
		IPanswerC = new InPutBox(76, 1, 12, 13);
		IPanswerC->setColor(colorbk_white | color_blue);
		*Events += IPanswerC;
		//
		IPanswerD = new InPutBox(76, 1, 12, 16);
		IPanswerD->setColor(colorbk_white | color_blue);
		*Events += IPanswerD;
		//
		IPanswer = new InPutBox(76, 1, 12, 19);
		IPanswer->setColor(colorbk_white | color_blue);
		*Events += IPanswer;


		LBQuestion = new ListBox<Question>(88, 30, 0, 24);
		LBQuestion->setColor(_bkcolor | color_grey);
		LBQuestion->setStrTiltle("Danh Sach Cau Hoi ");
		LBQuestion->setActionButton(bind(&ImpQuestion::ActionListQuestion, this, _1));
		*Events += LBQuestion;

		//
		int gy = getheight() - 4;
		btnAdd = new Button(6, 1, 40, gy);
		btnAdd->setText("Them");
		btnAdd->setActionButton(bind(&ImpQuestion::actionAdd, this, _1));
		*Events += btnAdd;
		//
		btnExit = new Button(6, 1, 50, gy);
		btnExit->setText("Thoat");
		btnExit->setActionButton(bind(&ImpQuestion::actionExit, this, _1));
		*Events += btnExit;
		//
		nObj = 16;
		Showobj = new window * [nObj];

		Showobj[0] = CLObject;
		Showobj[1] = Lquest;
		Showobj[2] = LanswerA;
		Showobj[3] = LanswerB;
		Showobj[4] = LanswerC;
		Showobj[5] = LanswerD;
		Showobj[6] = Lanswer;
		Showobj[7] = IPquest;
		Showobj[8] = IPanswerA;
		Showobj[9] = IPanswerB;
		Showobj[10] = IPanswerC;
		Showobj[11] = IPanswerD;
		Showobj[12] = IPanswer;
		Showobj[13] = LBQuestion;
		Showobj[14] = btnAdd;
		Showobj[15] = btnExit;
		//
		setlists(_Context->MonHocs->ToList());
	}

private:
	bool conditionfiltersv(Question* qs, int index, Monhoc* mh) {
		return qs->getIdObject() == mh->getId();
	}
	bool forEachMonHoc(Monhoc* mh, int index) {
		IList<Question>* temps = _treeQuestion->filter([&](Question* qs, int index) {return this->conditionfiltersv(qs, index, mh); });
		mh->setTree((TreeAVL<Question>*)temps);
		return true;
	}
	void setlists(IList<Monhoc>* lstObject) {
		_treeQuestion = _Context->Questions->ToTree();
		lstObject->forEach([&](Monhoc* mh, int index) {return this->forEachMonHoc(mh, index); });
		CLObject->setListObj(lstObject);
	}
	void ActionListQuestion(EventConsole& evt) {
		if (_ObjectCurrent != CLObject->GetDataChecked()) {
			_ObjectCurrent = CLObject->GetDataChecked();
			LBQuestion->setListObj(_ObjectCurrent->GetTree());
			LBQuestion->showLObj();
		}
	}
	void actionAdd(EventConsole& evt) {
		Monhoc* tempSel = CLObject->GetDataChecked();
		if (tempSel == NULL) {
			warning war(70, 10, 5, colorbk_darkgreen | color_red);
			war.SetScreen(_hSCreen);
			war.setBtnCancel(0);
			war.settext("ban chua chon mon hoc!!!");
			war.action(evt);
			return;
		}
		//tim id
		int count = _ObjectCurrent->GetTree()->getCount();
		int idTemp = hash<string>{}(_ObjectCurrent->getId() + (char)(48 + count));
		Question tempQuestion;
		tempQuestion.setId(idTemp);
		while (_treeQuestion->searchValue(&tempQuestion) != NULL)
		{
			++count;
			idTemp = hash<string>{}(_ObjectCurrent->getId() + (char)(48 + count));
			tempQuestion.setId(idTemp);
		}

		Question* tempQuest = new Question(
			idTemp,
			IPquest->Gettext(),
			IPanswerA->Gettext(),
			IPanswerB->Gettext(),
			IPanswerC->Gettext(),
			IPanswerD->Gettext(),
			IPanswer->Gettext()[0]
		);
		tempQuest->setIdObject(_ObjectCurrent->getId());
		LBQuestion->addNode(tempQuest);
		_treeQuestion->InsertConst(tempQuest);
		_Context->Questions->Add(tempQuest);
	}
	void actionExit(EventConsole& evt) {
		Close();
	}
private:
	CheckList<Monhoc>* CLObject;
	Lable* Lquest, * LanswerA, * LanswerB, * LanswerC, * LanswerD, * Lanswer;
	InPutBox* IPquest, * IPanswerA, * IPanswerB, * IPanswerC, * IPanswerD, * IPanswer;
	Button* btnAdd, * btnExit;
	ListBox<Question>* LBQuestion;
	TreeAVL<Question>* _treeQuestion = NULL;
	Monhoc* _ObjectCurrent = NULL;
};

#endif // !Question_H
