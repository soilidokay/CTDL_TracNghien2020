#ifndef Login_H
#define Login_H
#include "Form.h"
#include <iostream>
#include "Formteach.h"
#include "FormStudent.h"
#include "ProfileUser.h"

using namespace std::placeholders;
using namespace std;

class Login :public Form
{
public:
	void constructor() override {
		nObj = 5;
		//lable tai khoan
		lbTaikhoan = new Label(10, 1, 0, 1);
		lbTaikhoan->setColor(_bkcolor);
		lbTaikhoan->settext("TAI KHOAN");
		//lbTaikhoan->setFunProcessKey(&this->process);
		//lable mat khau
		lbMatkhau = new Label(10, 1, 0, 5);
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

		if (txtTaiKhoan->isEmpty() && txtMatkhau->isEmpty()) {
			ShowWarning(_hSCreen, "Thong tin dang nhap khong duoc rong!");
			return;
		}

		if (txtTaiKhoan->Gettext() == "GV" && txtMatkhau->Gettext() == "GV") {
			FormTeach* Fteach = new FormTeach(this, colorbk_white);
			Fteach->show();
			ProfileUser::getInstance()->USerId = "GV";
			return;
		}
		else {
			Sinhvien svtemp;
			svtemp.setidstudent(txtTaiKhoan->Gettext());
			_LstStudent = _Context->SinhViens->ToList();
			node<Sinhvien>* sv = _LstStudent->search(&svtemp);
			if (sv != NULL && sv->info->getPass() == txtMatkhau->Gettext()) {
				FormStudent* fstudent = new FormStudent(this, 52, 20, colorbk_white);
				fstudent->show();
				ProfileUser::getInstance()->USerId = sv->info->getId();
				return;
			}
		}
		ShowWarning(_hSCreen, "Thong tin dang nhap sai, Vui long kiem tra lai!");

	}
private:
	Label* lbTaikhoan, * lbMatkhau;
	InPutBox* txtMatkhau, * txtTaiKhoan;
	Button* btnDangNhap;
	List<Sinhvien>* _LstStudent = NULL;
};

#endif // !Login_H

