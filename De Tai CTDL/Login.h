#ifndef Login_H
#define Login_H
#include "Form.h"
#include <iostream>
#include "Formteach.h"
using namespace std::placeholders;
using namespace std;

class Login :public Form
{
public:
	void constructor() override {
		nObj = 5;
		//lable tai khoan
		lbTaikhoan = new Lable(10, 1, 0, 1);
		lbTaikhoan->setColor(_bkcolor);
		lbTaikhoan->settext("TAI KHOAN");
		//lbTaikhoan->setFunProcessKey(&this->process);
		//lable mat khau
		lbMatkhau = new Lable(10, 1, 0, 5);
		lbMatkhau->setColor(_bkcolor);
		lbMatkhau->settext(" MAT KHAU");
		//input ta khoan
		txtTaiKhoan = new InPutBox(20, 1, 12, 1);
		txtTaiKhoan->setColor(color_cyan | _bkcolor);
		*Events += txtTaiKhoan;

		//input mat khau
		txtMatkhau = new InPutBox(20, 1, 12, 5);
		txtMatkhau->setColor(color_cyan | _bkcolor);
		txtMatkhau->setPassChar('*');
		*Events += txtMatkhau;

		//button dang nhap id =4
		btnDangNhap = new Button(9, 1, 20, 10);
		btnDangNhap->setText("DANG NHAP");
		btnDangNhap->setActionButton(std::bind(&Login::actionBtnLOgin, this, _1));
		*Events += btnDangNhap;

		//tao doi tuong chung

		Showobj = new window * [nObj];

		Showobj[0] = lbTaikhoan;
		Showobj[1] = lbMatkhau;
		Showobj[2] = txtTaiKhoan;
		Showobj[3] = txtMatkhau;
		Showobj[4] = btnDangNhap;
		//-------------------
		/*for (int i = 0; i < getwidth(); i++) {
		for (int j = 0; j < getheight(); j++) {
		gotoXY(i, j);
		cout << _area[j][i];
		}
		}
		_getch();*/
	}
	void show()override {
		Form::show();
	}

	Login(Form* vbackup, int width, int height, int bkcolor) :
		Form(vbackup, width, height, bkcolor) {
		constructor();
		setEventMouseOrKey();
		DrawToScreen();
	}
	~Login() {
	}
private:
	void actionBtnLOgin(EventConsole& evt) {
		gotoXY(30, 0);
		scl::TextColor(_hSCreen, _bkcolor);
		if (txtTaiKhoan->Gettext() == "GV" && txtMatkhau->Gettext() == "GV") {
			FormTeach* Fteach = new FormTeach(NULL, 52, 25, colorbk_white);
			Fteach->show();
		}
		else if (!txtTaiKhoan->isEmpty() && !txtMatkhau->isEmpty()) {
			scl::TextColor(_hSCreen, color_red | _bkcolor);
			gotoXY(_hSCreen, 3, 8);
			cout << "thong tin dang nhap sai !!!";
			gotoXY(_hSCreen, 3, 9);
			cout << "Vui long, kiem tra lai!";
		}
	}
private:
	Lable* lbTaikhoan, * lbMatkhau;
	InPutBox* txtMatkhau, * txtTaiKhoan;
	Button* btnDangNhap;
};

#endif // !Login_H

