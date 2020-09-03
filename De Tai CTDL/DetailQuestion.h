#ifndef DETAIL_QUESTION_H
#define DETAIL_QUESTION_H

#include "Form.h"

class DetailQuestion : public Form
{
public:
	DetailQuestion(Form* Fbackup, int bkcolor = colorbk_white) : Form(Fbackup, 93, 60, bkcolor) {
		constructor();
		setEventMouseOrKey();
		DrawToScreen();
	}
	void constructor() override {
		//CheckList Object
		_CLObject = new CheckList<Monhoc>(50, 20, 2, Events);
		_CLObject->setheightLB(15);
		_CLObject->setColor(_bkcolor | color_grey);
		_CLObject->setStrTiltle("Mon Hoc");
		_CLObject->setGroupEle(false);
		_CLObject->setActionCollapse(bind(&DetailQuestion::ActionListObject, this, _1));
		*Events += _CLObject;
		//CheckList Class
		_CLStudent = new CheckList<Sinhvien>(80, 5, 6, Events);
		_CLStudent->setheightLB(15);
		_CLStudent->setColor(_bkcolor | color_grey);
		_CLStudent->setStrTiltle("Sinh Vien");
		_CLStudent->setGroupEle(false);
		_CLStudent->setActionCollapse(bind(&DetailQuestion::ActionListClasses, this, _1));
		*Events += _CLStudent;
		//ListBox Class
		_LBQustion = new ListBox<ModelQuestion>(90, 30, 0, 10);
		_LBQustion->setColor(_bkcolor | color_grey);
		_LBQustion->setStrTiltle("Chi Tiet cau hoi");
		_LBQustion->setActionItemClick(bind(&DetailQuestion::ActionListQuestion, this, _1));
		*Events += _LBQustion;
		//btn exit
		Lquest = new Label(90, 1, 0, 42);
		Lquest->settext("");
		Lquest->setColor(colorbk_cyan | color_grey);

		LanswerA = new Label(90, 1, 0, 45);
		LanswerA->settext("");
		LanswerA->setColor(colorbk_cyan | color_grey);

		LanswerB = new Label(90, 1, 0, 48);
		LanswerB->settext("");
		LanswerB->setColor(colorbk_cyan | color_grey);

		LanswerC = new Label(90, 1, 0, 51);
		LanswerC->settext("");
		LanswerC->setColor(colorbk_cyan | color_grey);

		LanswerD = new Label(90, 1, 0, 54);
		LanswerD->settext("");
		LanswerD->setColor(colorbk_cyan | color_grey);

		BtnExit = new Button(6, 1, 80, 2);
		BtnExit->setText("Thoat");
		BtnExit->setActionButton(bind(&DetailQuestion::actionExit, this, _1));
		*Events += BtnExit;


		nObj = 9; Showobj = new window * [nObj];
		Showobj[0] = _CLObject;
		Showobj[1] = _CLStudent;
		Showobj[2] = _LBQustion;
		Showobj[3] = Lquest;
		Showobj[4] = LanswerA;
		Showobj[5] = LanswerB;
		Showobj[6] = LanswerC;
		Showobj[7] = LanswerD;
		Showobj[8] = BtnExit;
		setlists(_Context->MonHocs->ToArrayList(300));
	}
	~DetailQuestion() {
		_TreeQuestion->Clear(true);
		delete _TreeQuestion;
		_lstQuestion->Clear();
		delete _lstQuestion;
	}
private:
	void actionExit(EventConsole& evt) {
		Close();
	}
	void setlists(IList<Monhoc>* lstobj) {
		_CLObject->setListObj(lstobj);
		_CLStudent->setListObj(_Context->SinhViens->ToList());
		_TreeQuestion = _Context->Questions->ToTree();
	}
	void ActionListObject(EventConsole& evt) {
		this->ShowListDetailQuestion();
	}
	void ActionListClasses(EventConsole& evt) {
		this->ShowListDetailQuestion();
	}
	void ShowListDetailQuestion() {
		Monhoc* mh = _CLObject->GetDataChecked();
		if (mh == NULL) {
			return;
		}
		Sinhvien* sv = _CLStudent->GetDataChecked();
		if (sv == NULL) {
			return;
		}

		// get BangDiems and filter nodeBangDiem for id MonHoc vs id SinhVien
		std::string idMD = mh->getId() + sv->getId();
		List<ModelDetailQuestion>* lstDetail = (List<ModelDetailQuestion>*) _Context->BangDiems
			->ToList()
			->filter([&](ModelDetailQuestion* md, int index) {return md->getMhAndSv() == idMD; });


		_lstQuestion = (List<ModelQuestion>*) _LBQustion->getListObj();
		if (_lstQuestion != NULL) {
			_lstQuestion->Clear();
			delete _lstQuestion;
		}

		_lstQuestion = new List<ModelQuestion>();
		Question tempq;
		lstDetail->forEach([&](ModelDetailQuestion* md, int index) {

			tempq.setId(md->getIdQuestion());
			Question* q = _TreeQuestion->searchValue(&tempq);
			ModelQuestion* mq = new ModelQuestion();
			mq->setQuest(q->getQuest());
			mq->setanswerA(q->getanswerA());
			mq->setanswerB(q->getanswerB());
			mq->setanswerC(q->getanswerC());
			mq->setanswerD(q->getanswerD());
			mq->setId(q->getId());
			char ch[2] = { md->getAnswer() + 65 ,'\0' };
			string answer = md->getAnswer() >= 0 ? string(ch) : "_";
			char h = q->getAnserw();
			mq->setAnswers(answer + "-dap an dung: " + h);
			_lstQuestion->insertlast(mq);
			return true;
			});

		_LBQustion->setListObj(_lstQuestion);
		_LBQustion->showLObj();

		lstDetail->Clear(true);
		delete lstDetail;
	}
	void ActionListQuestion(EventConsole& evt) {
		ModelQuestion* mq = _LBQustion->getSelected();
		if (mq == NULL) return;
		Lquest->UpdateText(mq->getQuest());
		LanswerA->UpdateText(mq->getanswerA());
		LanswerB->UpdateText(mq->getanswerB());
		LanswerC->UpdateText(mq->getanswerC());
		LanswerD->UpdateText(mq->getanswerD());
	}

	CheckList<Sinhvien>* _CLStudent;
	CheckList<Monhoc>* _CLObject;
	ListBox<ModelQuestion>* _LBQustion;
	TreeAVL<Question>* _TreeQuestion;
	List<ModelQuestion>* _lstQuestion;
	Label* Lquest, * LanswerA, * LanswerB, * LanswerC, * LanswerD;
	Button* BtnExit = NULL;
};

#endif // !DETAIL_QUESTION_H
