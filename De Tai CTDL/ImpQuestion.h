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
		CLObject->setActionCollapse(bind(&ImpQuestion::ActionListObject, this, _1));
		*Events += CLObject;
		//
		Lquest = new Label(10, 1, 0, 4);
		Lquest->settext("Cau hoi");
		Lquest->setColor(colorbk_white | color_grey);
		//
		LanswerA = new Label(10, 1, 0, 7);
		LanswerA->settext("Dap an A");
		LanswerA->setColor(colorbk_white | color_grey);
		//
		LanswerB = new Label(10, 1, 0, 10);
		LanswerB->settext("Dap an B");
		LanswerB->setColor(colorbk_white | color_grey);
		//
		LanswerC = new Label(10, 1, 0, 13);
		LanswerC->settext("Dap an C");
		LanswerC->setColor(colorbk_white | color_grey);
		//
		LanswerD = new Label(10, 1, 0, 16);
		LanswerD->settext("Dap an D");
		LanswerD->setColor(colorbk_white | color_grey);
		//
		Lanswer = new Label(10, 1, 0, 19);
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
		CLanswer = new CheckList<ModelAnswer>(76, 12, 19, Events);
		CLanswer->setColor(_bkcolor | color_grey);
		CLanswer->setheightLB(15);
		CLanswer->setStrTiltle("Answer");
		CLanswer->setGroupEle(false);
		*Events += CLanswer;
		IList<ModelAnswer>* lstAnser = new ArrayList<ModelAnswer>(4);
		lstAnser->InsertConst(new ModelAnswer(0, 'A'));
		lstAnser->InsertConst(new ModelAnswer(1, 'B'));
		lstAnser->InsertConst(new ModelAnswer(2, 'C'));
		lstAnser->InsertConst(new ModelAnswer(3, 'D'));
		CLanswer->setListObj(lstAnser);

		LBQuestion = new ListBox<Question>(88, 30, 0, 24);
		LBQuestion->setColor(_bkcolor | color_grey);
		LBQuestion->setStrTiltle("Danh Sach Cau Hoi ");
		LBQuestion->setActionItemClick(bind(&ImpQuestion::ActionListQuestion, this, _1));
		*Events += LBQuestion;

		//button
		int gy = getheight() - 4;
		btnClear = new Button(6, 1, 30, gy);
		btnClear->setText("Moi");
		btnClear->setActionButton(bind(&ImpQuestion::actionClear, this, _1));
		*Events += btnClear;
		//
		btnAdd = new Button(6, 1, 40, gy);
		btnAdd->setText("Luu");
		btnAdd->setActionButton(bind(&ImpQuestion::actionAdd, this, _1));
		*Events += btnAdd;

		btnUpdate = new Button(6, 1, 50, gy);
		btnUpdate->setText("Sua");
		btnUpdate->setActionButton(bind(&ImpQuestion::actionUpdate, this, _1));
		*Events += btnUpdate;
		//
		btnExit = new Button(6, 1, 60, gy);
		btnExit->setText("Thoat");
		btnExit->setActionButton(bind(&ImpQuestion::actionExit, this, _1));
		*Events += btnExit;
		//
		nObj = 18;
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
		Showobj[12] = CLanswer;
		Showobj[13] = LBQuestion;
		Showobj[14] = btnClear;
		Showobj[15] = btnAdd;
		Showobj[16] = btnUpdate;
		Showobj[17] = btnExit;
		//
		setlists(_Context->MonHocs->ToList());
	}

private:
	bool conditionfiltersv(Question* qs, int index, Monhoc* mh) {
		return qs->getIdObject() == mh->getId();
	}
	// get all question with ObjectId
	bool forEachMonHoc(Monhoc* mh, int index) {
		IList<Question>* temps = _treeQuestion->filter([&](Question* qs, int index) {return this->conditionfiltersv(qs, index, mh); });
		mh->setLstQuestion((IList<Question>*)temps);
		return true;
	}
	void setlists(IList<Monhoc>* lstObject) {
		_treeQuestion = _Context->Questions->ToTree();
		// Loop Object and call func get question with IdMonHoc
		lstObject->forEach([&](Monhoc* mh, int index) {return this->forEachMonHoc(mh, index); });
		CLObject->setListObj(lstObject);
	}
	void ActionListQuestion(EventConsole& evt) {
		Question* temp = LBQuestion->getSelected();
		char anwser[2];
		anwser[0] = temp->getAnserw();
		anwser[1] = '\0';

		IPquest->setText(temp->getQuest());
		IPanswerA->setText(temp->getanswerA());
		IPanswerB->setText(temp->getanswerB());
		IPanswerC->setText(temp->getanswerC());
		IPanswerD->setText(temp->getanswerD());
		CLanswer->SetChecked(anwser[0] - 65);
	}
	void ActionListObject(EventConsole& evt) {
		if (_ObjectCurrent != CLObject->GetDataChecked()) {
			_ObjectCurrent = CLObject->GetDataChecked();
			LBQuestion->setListObj(_ObjectCurrent->GetLstQuetion());
			LBQuestion->showLObj();
		}
	}

	bool ValidateData() {
		return CLanswer->GetDataChecked() != NULL && !IPquest->isEmpty() && !IPanswerA->isEmpty() && !IPanswerB->isEmpty()
			&& !IPanswerC->isEmpty() && !IPanswerD->isEmpty();
	}

	void actionAdd(EventConsole& evt) {
		Monhoc* tempSel = CLObject->GetDataChecked();

		if (!ValidateData()) {
			ShowWarning(_hSCreen, "Ban chua nhap du thong tin!");
			return;
		}


		if (tempSel == NULL) {
			ShowWarning(_hSCreen, "ban chua chon mon hoc!!!");
			return;
		}
		//tim id
		int count = _ObjectCurrent->GetLstQuetion()->getSize();
		long long int idTemp = hash<string>{}(_ObjectCurrent->getId() + std::to_string(count));
		if (idTemp < 0) {
			++idTemp;
		}
		Question tempQuestion;
		tempQuestion.setId(idTemp);
		// check is valid equal Id Question
		while (_treeQuestion->searchValue(&tempQuestion) != NULL)
		{
			++count;
			idTemp = hash<string>{}(_ObjectCurrent->getId() + std::to_string(count));
			tempQuestion.setId(idTemp);
		}
		// TODO
		/*if (count < 0) {
			count++;
		}*/

		Question* tempQuest = new Question(
			idTemp,
			IPquest->Gettext(),
			IPanswerA->Gettext(),
			IPanswerB->Gettext(),
			IPanswerC->Gettext(),
			IPanswerD->Gettext(),
			CLanswer->GetDataChecked()->getAnswer()
		);
		tempQuest->setIdObject(_ObjectCurrent->getId());
		_treeQuestion->InsertConst(tempQuest);
		_Context->Questions->Add(tempQuest);
		LBQuestion->addNode(tempQuest);
	}
	void actionUpdate(EventConsole& evt) {
		Question* temp = LBQuestion->getSelected();

		if (!ValidateData()) {
			ShowWarning(_hSCreen, "Ban chua nhap du thong tin!");
			return;
		}
		if (temp == NULL) return;

		temp->setQuest(IPquest->Gettext());
		temp->setanswer(CLanswer->GetDataChecked()->getAnswer());
		temp->setanswerA(IPanswerA->Gettext());
		temp->setanswerB(IPanswerB->Gettext());
		temp->setanswerC(IPanswerC->Gettext());
		temp->setanswerD(IPanswerD->Gettext());
		LBQuestion->showLObj();
		_Context->Questions->Update(temp);
	}
	void actionClear(EventConsole& evt) {
		IPquest->setText("");
		CLanswer->SetChecked(-1);
		IPanswerA->setText("");
		IPanswerB->setText("");
		IPanswerC->setText("");
		IPanswerD->setText("");
	}
	void actionExit(EventConsole& evt) {
		Close();
	}
private:
	CheckList<Monhoc>* CLObject;
	CheckList<ModelAnswer>* CLanswer;
	Label* Lquest, * LanswerA, * LanswerB, * LanswerC, * LanswerD, * Lanswer;
	InPutBox* IPquest, * IPanswerA, * IPanswerB, * IPanswerC, * IPanswerD;
	Button* btnAdd, * btnUpdate, * btnClear, * btnExit;
	ListBox<Question>* LBQuestion;
	TreeAVL<Question>* _treeQuestion = NULL;
	Monhoc* _ObjectCurrent = NULL;
};

#endif // !Question_H
