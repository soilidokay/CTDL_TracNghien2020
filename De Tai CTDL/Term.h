#ifndef TERM_H
#define TERM_H
#include "Form.h"
#include "ProfileUser.h"
class Term : public Form {
public:
	Term(Form* Fbackup, int bkcolor, IList<Question>* lstQuestion, int time) :
		Form(Fbackup, 80, 30, bkcolor)
	{
		constructor();
		setEventMouseOrKey();
		DrawToScreen();
		_LstQuestion = lstQuestion;

		int hour = time / 60;
		int minute = time % 60;

		timer = new TimeClock({ hour,minute,0 }, colorbk_cyan | colorbk_blue, 35, 4);
		timer->SetOnEnd([this] {this->onTimerEnd(); });
		_thread = new thread([&] {timer->printClock(&TimeClock::changetimeMult); });
		ArrAnswers = new ArrayList<ModelDetailQuestion>(_LstQuestion->getSize());

		for (int i = 0; i < _LstQuestion->getSize(); i++)
		{
			Question* q = _LstQuestion->GetData(i);
			ArrAnswers->Insert(new ModelDetailQuestion(
				q->getIdObject() + ProfileUser::getInstance()->USerId,
				-1,
				q->getId()));
		}

		setQuestion(_LstQuestion->GetData(indexCurrent));
	}
	void onTimerEnd() {
		double mark = CalculateMark();
		ShowWarning(_hSCreen, "Diem Cua Ban:" + to_string(mark).substr(0, 4));

		string MaMh = _LstQuestion->GetData(0)->getIdObject();
		Diem tempdiem(MaMh, ProfileUser::getInstance()->USerId, mark);
		Diem* tempPtrDiem = _Context->Diems->Seach(&tempdiem);
		if (tempPtrDiem != NULL) {
			if (mark > tempPtrDiem->getScores()) {
				_Context->Diems->Update(&tempdiem);
			}
		}
		else
		{
			_Context->Diems->Add(&tempdiem);
		}
		ArrAnswers->forEach([&](ModelDetailQuestion * md,int index) {
			if (_Context->BangDiems->isExit(md->getId())) {
				_Context->BangDiems->Update(md);
			}
			else {
				_Context->BangDiems->Add(md);
			}
			return true;
			});
		Close();
	}
	void constructor()override {

		LQuestion = new Label(76, 1, 1, 1);
		LQuestion->setColor(colorbk_white | color_grey);
		//-----------------
		BtnA = new Button(76, 1, 1, 7);
		BtnA->setTextCenter(false);
		BtnA->setActionButton(bind(&Term::ActionA, this, _1));
		*Events += BtnA;
		//------------------
		btnB = new Button(76, 1, 1, 11);
		btnB->setActionButton(bind(&Term::ActionB, this, _1));
		btnB->setTextCenter(false);
		*Events += btnB;
		//-------------------
		btnC = new Button(76, 1, 1, 15);
		btnC->setActionButton(bind(&Term::ActionC, this, _1));
		btnC->setTextCenter(false);
		*Events += btnC;
		//---------------------
		btnD = new Button(76, 1, 1, 19);
		btnD->setActionButton(bind(&Term::ActionD, this, _1));
		btnD->setTextCenter(false);
		*Events += btnD;
		//-------------------


		btnPrev = new Button(10, 1, 20, 26);
		btnPrev->setText("Tro lai");
		btnPrev->setActionButton(bind(&Term::ActionPrev, this, _1));
		*Events += btnPrev;

		btnSummit = new Button(10, 1, 33, 26);
		btnSummit->setText("Nop Bai");
		btnSummit->setActionButton(bind(&Term::ActionSummit, this, _1));
		*Events += btnSummit;

		btnNext = new Button(10, 1, 46, 26);
		btnNext->setText("Tiep Theo");
		btnNext->setActionButton(bind(&Term::ActionNext, this, _1));
		*Events += btnNext;
		//-------------------
		nObj = 8;
		Showobj = new window * [nObj];
		Showobj[0] = BtnA;
		Showobj[1] = btnB;
		Showobj[2] = btnC;
		Showobj[3] = btnD;
		Showobj[4] = btnSummit;
		Showobj[5] = btnPrev;
		Showobj[6] = btnNext;
		Showobj[7] = LQuestion;

		//--------------------
	}
	void SyncData() {

	}

	~Term() {
		timer->stop();
		delete timer;
		_thread->join();
		delete _thread;
		_LstQuestion->Clear();
		delete _LstQuestion;
		ArrAnswers->Clear();
		delete ArrAnswers;
	}
private:
	void setQuestion(Question* data) {
		LQuestion->UpdateText("cau " + to_string(indexCurrent + 1) +
			"/" + to_string(_LstQuestion->getSize()) + ":" + data->getQuest());
		BtnA->UpdateText("A:" + data->getanswerA());
		btnB->UpdateText("B:" + data->getanswerB());
		btnC->UpdateText("C:" + data->getanswerC());
		btnD->UpdateText("D:" + data->getanswerD());
		int answer = ArrAnswers->GetData(indexCurrent)->getAnswer();
		if (answer >= 0) {
			setBtnAction((Button*)Showobj[answer]);
		}
		else {
			setBtnAction(NULL);
		}

	}
	void setBtnAction(Button* btn) {
		if (btnActive != NULL) btnActive->show();
		if (btn == NULL) return;
		btnActive = btn;
		btnActive->UpdateBackGround(colorbk_green);
	}
	void ActionA(EventConsole& evt) {
		setBtnAction(BtnA);
		ArrAnswers->GetData(indexCurrent)->setAnswer(0);
	}
	void ActionB(EventConsole& evt) {
		setBtnAction(btnB);
		ArrAnswers->GetData(indexCurrent)->setAnswer(1);
	}
	void ActionC(EventConsole& evt) {
		setBtnAction(btnC);
		ArrAnswers->GetData(indexCurrent)->setAnswer(2);
	}
	void ActionD(EventConsole& evt) {
		setBtnAction(btnD);
		ArrAnswers->GetData(indexCurrent)->setAnswer(3);
	}
	void ActionPrev(EventConsole& evt) {
		if (indexCurrent > 0) {
			--indexCurrent;
			setQuestion(_LstQuestion->GetData(indexCurrent));
		}
	}
	double CalculateMark() {
		int mark = 0;
		for (int i = 0; i < _LstQuestion->getSize(); i++)
		{
			if (ArrAnswers->GetData(i)->getAnswer() + 65 == _LstQuestion->GetData(i)->getAnserw()) {
				++mark;
			}
		}
		return mark * 10.0 / _LstQuestion->getSize();
	}
	void ActionSummit(EventConsole& evt) {
		timer->stop();

	}
	void ActionNext(EventConsole& evt) {
		if (indexCurrent < _LstQuestion->getSize() - 1) {
			++indexCurrent;
			setQuestion(_LstQuestion->GetData(indexCurrent));
		}

	}


private:
	Label* LQuestion;
	Button* BtnA, * btnB, * btnD, * btnC, * btnSummit, * btnPrev, * btnNext, * btnActive = NULL;
	TimeClock* timer;
	IList<Question>* _LstQuestion;
	ArrayList<ModelDetailQuestion>* ArrAnswers;
	int indexCurrent = 0;
	thread* _thread;
};


#endif // !TERM_H
