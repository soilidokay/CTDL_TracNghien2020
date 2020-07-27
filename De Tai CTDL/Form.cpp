#include "Form.h"
#include "EventController.h"
Form::Form(Form* Fbackup, int width, int height, int bkcolor)
{
	_Fbackup = Fbackup;
	_bkcolor = bkcolor;

	COORD WinInfo = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));

	_width = width > WinInfo.X ? WinInfo.X : width;
	_height = height > WinInfo.Y ? WinInfo.Y : height;

	_area = new int* [_height];
	for (int i = 0; i < _height; ++i) _area[i] = new int[_width];
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


int customtext(std::string& text, int lenmax) {
	int len = text.length();
	int buff = len / lenmax;
	int plus = len % lenmax;
	if (plus == 0) {
		--buff;
	}

	for (int i = 1; i <= buff; i++)
	{
		int posSpace = i * lenmax;
		while (posSpace > 0 && text[posSpace] != ' ') posSpace--;
		text.insert(text.begin() + posSpace, '\n');
	}
	return buff + 1;
}

const int WidthWar = 40;

bool ShowWarning(HANDLE _hSCreen, std::string text, bool isCancel)
{
	CONSOLE_SCREEN_BUFFER_INFO cisbi = {};
	GetConsoleScreenBufferInfo(_hSCreen, &cisbi);

	int Width = WidthWar > cisbi.dwSize.X ? cisbi.dwSize.X : WidthWar;

	EventConsole evt;
	int row = customtext(text, Width - 4);

	warning war(_hSCreen, Width - 2, row + 5, 0, 0, colorbk_darkgreen | color_red);
	war.setBtnCancel(isCancel);
	war.settext(text);
	EventController::getInstance()->setIdLock(true);
	war.action(evt);
	EventController::getInstance()->setIdLock(false);
	return war.GetOK();
}