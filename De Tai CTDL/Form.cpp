#include "Form.h"

Form::Form(Form* Fbackup, int width, int height, int bkcolor)
{
	_Fbackup = Fbackup;
	_bkcolor = bkcolor;
	_width = width;
	_height = height;
	_area = new int* [height];
	for (int i = 0; i < height; ++i) _area[i] = new int[width];
	for (int i = 0; i < _width; i++)
		for (int j = 0; j < _height; j++)
			_area[j][i] = -1;
	EventController* HandleEventController = EventController::getInstance();
	this->Events = new EventMouseOrKey();

	*HandleEventController += this->Events;

	init();

}
void Form::Close()
{
	delete this;
}

Form::~Form()
{
	EventController* HandleEventController = EventController::getInstance();
	*HandleEventController -= this->Events;
	delete this->Events;
	for (int i = 0; i < nObj; i++) delete Showobj[i];
	delete[] Showobj;
	for (int i = 0; i < _height;) delete[] _area[i++];
	delete[] _area;
	if (_Fbackup != NULL) _Fbackup->backup();
	delete _StreamBuff;
	DeleteScreenBuff(_hSCreen);
}

void Form::DrawToScreen()
{
	for (int i = 0; i < nObj; ++i) {
		Showobj[i]->SetScreen(_hSCreen);
		Showobj[i]->show();
	}
}

void ShowWarning(HANDLE _hSCreen, std::string text)
{
	EventConsole evt;
	warning war(70, 10, 5, colorbk_darkgreen | color_red);
	war.SetScreen(_hSCreen);
	war.setBtnCancel(0);
	war.settext(text);
	war.action(evt);
}