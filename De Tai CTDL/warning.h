#ifndef WARNING_h
#define WARNING_h

#include "Window.h"
#include "Button.h"

class warning :public window
{
public:
	warning(int width, int x, int y,int color) : window(width > 40 ? 40 : width , 6, x, y) {
		setColor(color);
		//---btn ok
		int xt = getwidth() + x;
		int yt = getheight() + y;
		bCancel = 1;
		btnOk = new Button(6, 1, xt - 20, yt - 2);
		btnOk->setText("OK");
		//btn cancel
		btnCan = new Button(6, 1, xt - 9, yt - 2);
		btnCan->setText("CANCEL");
		_Ok = 0;
	};
	void setBtnCancel(bool bcancel) { bCancel = bcancel; }
	void settext(std::string strtext) { _strText = strtext; }
	void showtext() {
		gotoXY(_hScreen,getx() + 1, gety() + 1);
		scl::TextColor(_hScreen,getcolor());
		std::cout << _strText.substr(0, getwidth());
	}
	bool GetOK() { return _Ok; }
	void SetScreen(HANDLE hscreen) override {
		_hScreen = hscreen;
		if (bCancel) btnCan->SetScreen(hscreen);
		btnOk->SetScreen(hscreen);
	}
	void show()override {
		window::show();
		showtext();
		btnOk->show();
		if(bCancel) btnCan->show();
	}
	void action(EventConsole& evt)override {
		CHAR_INFO *BkWindow = showWindow();
		int chkMouse = 0;
		do
		{
			KeyMouse(&evt);
			chkMouse = checkMouse(evt);
		} while (chkMouse == 0);
		if (chkMouse == 1) {
			_Ok = 1;
			btnOk->action(evt);
		}
		else if(bCancel) {
			_Ok = 0;
			btnCan->action(evt);
		}
		backup(BkWindow);
	}
	~warning() {
		delete btnOk;
		delete btnCan;
	};

private:
	CHAR_INFO* showWindow() {
		SHORT height = getheight() + 3;
		SHORT width = getwidth() + 3;
		SHORT x = getx();
		SHORT y = gety();
		CHAR_INFO *charac = new CHAR_INFO[height*width];
		scl::ReadBlockChar(_hScreen,charac, height, width, x, y);
		show();
		return charac;
	}
	void backup(CHAR_INFO *charac) {
			SHORT height = getheight() + 3;
			SHORT width = getwidth() + 3;
			SHORT x = getx();
			SHORT y = gety();
			scl::WriteBlockChar(_hScreen,charac, height, width, x, y);
			//sety(gety() + 9);
	}
	int checkMouse(EventConsole& evt) {
		int xt = btnOk->getx();
		int yt = btnOk->gety();
		if (evt._Smouse.x >= xt && evt._Smouse.x <= xt + btnOk->getwidth() + 1 &&
			evt._Smouse.y >= yt && evt._Smouse.y <= yt + btnOk->getheight()+1) {
			return 1;
		}
		xt = btnCan->getx();
		yt = btnCan->gety();
		if (evt._Smouse.x >= xt && evt._Smouse.x <= xt + btnOk->getwidth()+1 &&
			evt._Smouse.y >= yt && evt._Smouse.y <= yt + btnOk->getheight()+1) {
			return 2;
		}
		return 0;
	}
private:
	bool _Ok;
	bool bCancel;
	std::string _strText;
	Button *btnOk, *btnCan;
};


#endif // !WARNING_h
