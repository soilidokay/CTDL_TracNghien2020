#ifndef INPORTINFOTERM
#define INPORTINFOTERM

#include "Form.h"
#include "AppDbContext.h"
#include "Term.h"
#include <cstdlib>
#include <ctime>

class ImportInfoTerm : public Form
{
public:
	ImportInfoTerm(Form* Fbackup, int width, int height, int bkcolor) : Form(Fbackup, width, height, bkcolor)
	{
		constructor();
		setEventMouseOrKey();
		DrawToScreen();
	}
	void constructor()override {
		//Listbox lop
		//
		CLObject = new CheckList<Monhoc>(46, 0, 1, Events);
		CLObject->setColor(_bkcolor | color_grey);
		CLObject->setheightLB(10);
		CLObject->setGroupEle(false);
		CLObject->setStrTiltle("Danh sach mon hoc ");
		*Events += CLObject;
		//lable Ma lop
		LAmountQuestion = new Label(20, 1, 0, 4);
		LAmountQuestion->settext("So Luong Cau hoi");
		LAmountQuestion->setColor(colorbk_white | color_grey);
		*Events += LAmountQuestion;

		//lable ten lop
		LTime = new Label(20, 1, 0, 7);
		LTime->settext("So Phut Thi");
		LTime->setColor(colorbk_white | color_grey);
		//inputbox idclass
		IpAmountQuetion = new InPutBox(25, 1, 21, 4);
		IpAmountQuetion->setColor(colorbk_white | color_blue);
		IpAmountQuetion->SetisNumber(true);
		*Events += IpAmountQuetion;
		//inputbox nameclass
		IpTime = new InPutBox(25, 1, 21, 7);
		IpTime->setColor(colorbk_white | color_blue);
		IpTime->SetisNumber(true);
		*Events += IpTime;
		//-------Button Clear
		btnClear = new Button(6, 1, 10, 15);
		btnClear->setText("Clear");
		btnClear->setActionButton(bind(&ImportInfoTerm::ActionClear, this, _1));
		*Events += btnClear;
		//-------Botton them
		btnTerm = new Button(6, 1, 19, 15);
		btnTerm->setText("Thi");
		btnTerm->setActionButton(bind(&ImportInfoTerm::ActionTerm, this, _1));
		*Events += btnTerm;
		//-------Botton thoat
		btnExit = new Button(6, 1, 28, 15);
		btnExit->setText("Thoat");
		btnExit->setActionButton(bind(&ImportInfoTerm::ActionExit, this, _1));
		*Events += btnExit;
		//-----------------

		nObj = 8;
		Showobj = new window * [nObj];

		Showobj[0] = CLObject;
		Showobj[1] = LAmountQuestion;
		Showobj[2] = LTime;
		Showobj[3] = IpAmountQuetion;
		Showobj[4] = IpTime;
		Showobj[5] = btnClear;
		Showobj[6] = btnTerm;
		Showobj[7] = btnExit;

		setlists(_Context->MonHocs->ToArrayList(300));
	}


private:
	void setlists(IList<Monhoc>* lstObj) {
		_treeQuestion = _Context->Questions->ToTree();
		lstObj->forEach([&](Monhoc* mh, int index) {return this->forEachMonHoc(mh, index); });
		CLObject->setListObj(lstObj);
	}
	bool conditionfiltersv(Question* qs, int index, Monhoc* mh) {
		return qs->getIdObject() == mh->getId();
	}
	bool forEachMonHoc(Monhoc* mh, int index) {
		IList<Question>* temps = _treeQuestion->filter([&](Question* qs, int index) {return this->conditionfiltersv(qs, index, mh); });
		mh->setLstQuestion((IList<Question>*)temps);
		return true;
	}
	//action button
	void ActionClear(EventConsole& evt) {
		IpAmountQuetion->setText("");
		IpTime->setText("");
	}
	void shuffle(int* arr, int n) {
		srand(time(NULL));
		int res = rand();
		for (int i = n - 1; i >= 0; i--) {
			int j = rand() % (n - i) + i; //Math.floor(Math.random() * (i + 1));
			swap(arr[i], arr[j]);
		}
	}
	IList<Question>* RandomQuestion(IList<Question>* lstQuestion, int amount) {
		int size = lstQuestion->getSize();
		int* a = new int[size];
		for (int i = 0; i < size; i++)
		{
			a[i] = i;
		}
		shuffle(a, size);
		IList<Question>* lstTemp = new ArrayList<Question>(amount);

		for (int i = 0; i < amount && i < size; i++)
		{
			lstTemp->InsertConst(lstQuestion->GetData(a[i]));
		}

		delete[]a;
		return lstTemp;
	}
	void ActionTerm(EventConsole& evt) {
		Monhoc* mh = CLObject->GetDataChecked();
		if (mh == NULL) {
			ShowWarning(_hSCreen, "Ban chua chon mon hoc!");
			return;
		}
		if (IpTime->isEmpty() || IpAmountQuetion->isEmpty()) {
			ShowWarning(_hSCreen, "Ban chua nhap day du thong tin!");
			return;
		}
		IList<Question>* lstQuestion = mh->GetLstQuetion();
		int AmountQuestionm = atoi(IpAmountQuetion->Gettext().c_str());
		if (AmountQuestionm > lstQuestion->getSize()) {
			ShowWarning(_hSCreen, "So luong cau hoi khong du!");
			return;
		}
		int time = atoi(IpTime->Gettext().c_str());
		Term* term = new Term(this, colorbk_white, RandomQuestion(lstQuestion, AmountQuestionm), time);
		term->show();
	}
	void ActionExit(EventConsole& evt) {
		Close();
	}
private:
	CheckList<Monhoc>* CLObject;
	Label* LAmountQuestion, * LTime;
	InPutBox* IpAmountQuetion, * IpTime;
	Button* btnClear, * btnTerm, * btnExit;
	TreeAVL<Question>* _treeQuestion = NULL;
};

#endif // !INPORTINFOTERM
