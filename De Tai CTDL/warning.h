#ifndef WARNING_h
#define WARNING_h

#include "Window.h"
#include "Button.h"

class warning :public window
{
public:
	warning(HANDLE HScreen, int width, int height, int x, int y, int color) : window(width, height, x, y) {
		setColor(color);
		_hScreen = HScreen;
		CONSOLE_SCREEN_BUFFER_INFO cisbi = {};
		GetConsoleScreenBufferInfo(_hScreen, &cisbi);

		setx((cisbi.dwSize.X - width) / 2 - 1);
		sety((cisbi.dwSize.Y - height) / 2 - 1);


		//---btn ok
		int xt = getwidth() + getx();
		int yt = getheight() + gety();
		bCancel = 1;
		btnOk = new Button(6, 1, xt - 13, yt - 2);
		btnOk->SetScreen(_hScreen);
		btnOk->setText("OK");
		//btn cancel
		btnCan = new Button(6, 1, xt - 7, yt - 2);
		btnCan->setText("CANCEL");
		btnCan->SetScreen(_hScreen);
		_Ok = 0;
	};
	void setBtnCancel(bool bcancel) { bCancel = bcancel; }
	void settext(std::string strtext) { _strText = strtext; }
	void showtext() {
		size_t pos = 0, posstrart = 0;
		std::string s = _strText;
		scl::TextColor(_hScreen, getcolor());
		int index = 1;
		while ((pos = s.find('\n')) != std::string::npos) {
			gotoXY(_hScreen, getx() + 1, gety() + index++);
			std::cout << s.substr(0, pos);
			s.erase(0, pos + 1);
		}
		gotoXY(_hScreen, getx() + 1, gety() + index++);
		std::cout << s;
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
		if (bCancel) btnCan->show();
	}
	void action(EventConsole& evt)override {
		CHAR_INFO* BkWindow = showWindow();
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
		else if (bCancel) {
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
		CHAR_INFO* charac = new CHAR_INFO[height * width];
		scl::ReadBlockChar(_hScreen, charac, height, width, x, y);
		show();
		return charac;
	}
	void backup(CHAR_INFO* charac) {
		SHORT height = getheight() + 3;
		SHORT width = getwidth() + 3;
		SHORT x = getx();
		SHORT y = gety();
		scl::WriteBlockChar(_hScreen, charac, height, width, x, y);
		//sety(gety() + 9);
	}
	int checkMouse(EventConsole& evt) {
		int xt = btnOk->getx();
		int yt = btnOk->gety();
		if (evt._Smouse.x >= xt && evt._Smouse.x <= xt + btnOk->getwidth() + 1 &&
			evt._Smouse.y >= yt && evt._Smouse.y <= yt + btnOk->getheight() + 1) {
			return 1;
		}
		xt = btnCan->getx();
		yt = btnCan->gety();
		if (evt._Smouse.x >= xt && evt._Smouse.x <= xt + btnOk->getwidth() + 1 &&
			evt._Smouse.y >= yt && evt._Smouse.y <= yt + btnOk->getheight() + 1) {
			return 2;
		}
		return 0;
	}
private:
	bool _Ok;
	bool bCancel;
	std::string _strText;
	Button* btnOk, * btnCan;
};


#endif // !WARNING_h
