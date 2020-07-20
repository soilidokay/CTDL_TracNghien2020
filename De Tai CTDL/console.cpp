#include "console.h"
#include <iostream>

namespace scl {

	HANDLE whandConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE rhandleConsole = GetStdHandle(STD_INPUT_HANDLE);

	void DisableMaxiMize(LPCSTR title) {
		SetTitle(title);
		while (FindWindowA(NULL, title) == NULL);
		SetWindowLong(FindWindowA(NULL, title), GWL_STYLE,
			GetWindowLong(FindWindowA(NULL, title), GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	}
	void SetTitle(std::string title)
	{
		SetConsoleTitle(title.c_str());
	}

	void SizeConsole(SHORT Width, SHORT height)
	{
		SMALL_RECT SizeW = { 0,0,Width - 1,height - 1 };
		COORD sizebuff = { Width,height };
		BOOL BSize = SetConsoleWindowInfo(whandConsole, true, &SizeW);
		SetConsoleScreenBufferSize(whandConsole, sizebuff);
		if (!BSize) SetConsoleWindowInfo(whandConsole, true, &SizeW);
	}
	void SizeConsole(HANDLE hscreen, SHORT Width, SHORT height)
	{

		SMALL_RECT SizeW = { 0,0,Width - 1,height - 1 };
		COORD sizebuff = { Width,height };
		SetConsoleScreenBufferSize(hscreen, sizebuff);
		BOOL BSize = SetConsoleWindowInfo(hscreen, true, &SizeW);
	}
	void SizeBuffer(SHORT col, SHORT row)
	{
		COORD Sizebuf = { col,row };
		SetConsoleScreenBufferSize(whandConsole, Sizebuf);

	}
	void WriteChar(char ch, SHORT x, SHORT y, SHORT color)
	{
		CHAR_INFO chara;
		chara.Char.AsciiChar = ch;
		chara.Attributes = color;
		COORD sizebuff = { 1,1 };
		COORD pos = { 0,0 };
		SMALL_RECT earea = { x,y,x,y };
		WriteConsoleOutput(whandConsole, &chara, sizebuff, pos, &earea);
	}

	HANDLE CreateScreenBuff()
	{
		HANDLE hNewScreenBuffer = CreateConsoleScreenBuffer(
			GENERIC_READ |           // read/write access 
			GENERIC_WRITE,
			FILE_SHARE_READ |
			FILE_SHARE_WRITE,        // shared 
			NULL,                    // default security attributes 
			CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
			NULL);                   // reserved; must be NULL 
		return hNewScreenBuffer;
	}

	void DeleteScreenBuff(HANDLE hscreen) {
		CloseHandle(hscreen);
	}

	CHAR_INFO* GetScreenCurrent()
	{
		CONSOLE_SCREEN_BUFFER_INFO buffinfo;
		GetConsoleScreenBufferInfo(whandConsole, &buffinfo);
		int sizeChar = buffinfo.dwSize.X * buffinfo.dwSize.Y;
		CHAR_INFO* chiBuffer = new CHAR_INFO[sizeChar];
		COORD pos = { 0,0 };
		ReadConsoleOutput(
			whandConsole,        // screen buffer to read from 
			chiBuffer,      // buffer to copy into 
			buffinfo.dwSize,   // col-row size of chiBuffer 
			pos,  // top left dest. cell in chiBuffer 
			&buffinfo.srWindow); // screen buffer source rectangle 
		return chiBuffer;
	}

	void WriteBlockChar(char* Arraych,
		SHORT row, SHORT col,
		SHORT x, SHORT y,
		int color)
	{
		CHAR_INFO* charater = new CHAR_INFO[row * col];
		for (int i = 0; i < row * col; i++) charater[i].Char.AsciiChar = Arraych[i];
		COORD sizebuff = { col,row };
		COORD pos = { 0,0 };
		SMALL_RECT earea = { x,y,x + col - 1,y + row - 1 };
		TextColor(color);
		WriteConsoleOutput(whandConsole, charater, sizebuff, pos, &earea);
		delete[] charater;
	}
	void WriteBlockChar(CHAR_INFO* charater,
		SHORT row, SHORT col,
		SHORT x, SHORT y)
	{
		COORD sizebuff = { col,row };
		COORD pos = { 0,0 };
		SMALL_RECT earea = { x,y,x + col - 2,y + row - 2 };
		WriteConsoleOutput(whandConsole, charater, sizebuff, pos, &earea);
		delete[] charater;
	}
	void WriteBlockChar(HANDLE hscreen, CHAR_INFO* charater,
		SHORT row, SHORT col,
		SHORT x, SHORT y)
	{
		COORD sizebuff = { col,row };
		COORD pos = { 0,0 };
		SMALL_RECT earea = { x,y,x + col - 2,y + row - 2 };
		WriteConsoleOutput(hscreen, charater, sizebuff, pos, &earea);
		delete[] charater;
	}
	void ReadBlockChar(char* Arraych,
		SHORT row, SHORT col,
		SHORT x, SHORT y)
	{
		CHAR_INFO* charater = new CHAR_INFO[row * col];
		COORD sizebuff = { col,row };
		COORD pos = { 0,0 };
		SMALL_RECT earea = { x,y,x + col - 1,y + row - 1 };
		ReadConsoleOutput(whandConsole, charater, sizebuff, pos, &earea);
		for (int i = 0; i < row * col; i++) {
			Arraych[i] = charater[i].Char.AsciiChar;
		}
		delete[] charater;
	}
	void ReadBlockChar(CHAR_INFO* charater,
		SHORT row, SHORT col,
		SHORT x, SHORT y)
	{
		COORD sizebuff = { col,row };
		COORD pos = { 0,0 };
		SMALL_RECT earea = { x,y,x + col - 1,y + row - 1 };
		ReadConsoleOutput(whandConsole, charater, sizebuff, pos, &earea);
	}
	void ReadBlockChar(HANDLE hscreen, CHAR_INFO* charater,
		SHORT row, SHORT col,
		SHORT x, SHORT y)
	{
		COORD sizebuff = { col,row };
		COORD pos = { 0,0 };
		SMALL_RECT earea = { x,y,x + col - 1,y + row - 1 };
		ReadConsoleOutput(hscreen, charater, sizebuff, pos, &earea);
	}
	void fillBackGround(int col, int row, int color) {
		COORD pos = { 0,0 };
		DWORD nlen = col * row;
		DWORD nCharacter;
		if (!FillConsoleOutputAttribute(whandConsole, color, nlen, pos, &nCharacter))
			return;
	}
	void fillBackGround(HANDLE hscreen, int col, int row, int color) {
		COORD pos = { 0,0 };
		DWORD nlen = col * row;
		DWORD nCharacter;
		if (!FillConsoleOutputAttribute(hscreen, color, nlen, pos, &nCharacter))
			return;
	}
	int inputKey()
	{
		if (_kbhit())
		{
			int key = _getch();

			if (key == 224)	// special key
			{
				key = _getch();
				return key + 1000;
			}

			return key;
		}
		else
		{
			return key_none;
		}

		return key_none;
	}


	//-------------------------Screen-------------------------
	void clrscr()
	{
		CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
		HANDLE	hConsoleOut;
		COORD	Home = { 0,0 };
		DWORD	dummy;

		GetConsoleScreenBufferInfo(whandConsole, &csbiInfo);

		FillConsoleOutputCharacter(whandConsole, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
		csbiInfo.dwCursorPosition.X = 0;
		csbiInfo.dwCursorPosition.Y = 0;
		SetConsoleCursorPosition(whandConsole, csbiInfo.dwCursorPosition);
	}


	//screen: goto [x,y]
	void gotoXY(int column, int line)
	{
		COORD coord;
		coord.X = column;
		coord.Y = line;
		SetConsoleCursorPosition(whandConsole, coord);
	}

	void gotoXY(HANDLE hscreen, int column, int line)
	{
		COORD coord;
		coord.X = column;
		coord.Y = line;
		SetConsoleCursorPosition(hscreen, coord);
	}


	//screen: get [x]
	int whereX()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(whandConsole, &csbi))
			return csbi.dwCursorPosition.X;
		return -1;
	}


	//screen: get [y]
	int whereY()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(whandConsole, &csbi))
			return csbi.dwCursorPosition.Y;
		return -1;
	}

	int gettxtColor()
	{
		CONSOLE_SCREEN_BUFFER_INFO cisb;
		GetConsoleScreenBufferInfo(whandConsole, &cisb);
		return cisb.wAttributes;
	}
	int gettxtColor(HANDLE hscreen)
	{
		CONSOLE_SCREEN_BUFFER_INFO cisb;
		GetConsoleScreenBufferInfo(hscreen, &cisb);
		return cisb.wAttributes;
	}
	// Ẩn hiện con trỏ nhấp nháy trong cửa sổ Console
	void ShowCur(bool CursorVisibility)
	{
		CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
		SetConsoleCursorInfo(whandConsole, &cursor);
	}
	void ShowCur(HANDLE hscreen, bool CursorVisibility)
	{
		CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
		SetConsoleCursorInfo(hscreen, &cursor);
	}
	void TextColor(int color)
	{
		SetConsoleTextAttribute(whandConsole, color);
	}
	void TextColor(HANDLE hscreen, int color)
	{
		SetConsoleTextAttribute(hscreen, color);
	}


	//catch key and mouse
	void KeyMouse(EventConsole* eventcon) {
		//lay handle man hinh console
		bool runCath = 1;// thiet lap co che thoat
		bool clickMouse = 0;
		eventcon->_Smouse._kindMouse = MouseKind::none;
		eventcon->_key = -1;
		DWORD numberEvent = 0;
		INPUT_RECORD enventBuff[100];//= new INPUT_RECORD[numberEvent];
		//tao mang de luu cac event 
		DWORD rnumberEvent = 0;
		while (runCath)
		{
			WaitForSingleObject(rhandleConsole, 10000);
			//lay so luong event da xay ra
			GetNumberOfConsoleInputEvents(rhandleConsole, &numberEvent);
			if (numberEvent != 0) {//co su kien xay ra
				numberEvent = numberEvent > 100 ? 100 : numberEvent;
				//doc event vao man
				ReadConsoleInput(rhandleConsole, enventBuff, numberEvent, &rnumberEvent);
				for (DWORD i = 0; i < numberEvent; ++i) {
					if (enventBuff[i].EventType == MOUSE_EVENT) {//kiem tra co phai event mouse
						// lay toa do chuot
						eventcon->_Smouse.x = enventBuff[i].Event.MouseEvent.dwMousePosition.X;
						eventcon->_Smouse.y = enventBuff[i].Event.MouseEvent.dwMousePosition.Y;
						//kiem tra co phai chuot trai duoc nhan
						if (enventBuff[i].Event.MouseEvent.dwEventFlags & DOUBLE_CLICK) {
							eventcon->_Smouse._kindMouse = MouseKind::dleft;
							runCath = 0;
						}
						else if (enventBuff[i].Event.MouseEvent.dwEventFlags == 0 && enventBuff[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
							eventcon->_Smouse._kindMouse = MouseKind::left; ;
							runCath = 0;
						}
						//kiem tra co phai chuot phai nhan
						else if (enventBuff[i].Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) {
							eventcon->_Smouse._kindMouse = MouseKind::right;
							runCath = 0;
						}
						eventcon->KeyOrMouse = 1;
					}//kiem tra co phai event key
					else if (enventBuff[i].EventType == KEY_EVENT && enventBuff[i].Event.KeyEvent.bKeyDown) {
						if ((eventcon->_key = enventBuff[i].Event.KeyEvent.uChar.AsciiChar) == 0) {
							eventcon->_key = enventBuff[i].Event.KeyEvent.wVirtualScanCode + 1000;
						}
						eventcon->KeyOrMouse = 0;
						runCath = 0;
					}
				}
				//delete[] enventBuff;
			}// if
			Sleep(10);
		}// while
	}

	void clrscr(int col, int row, char ch) {
		COORD pos = { 0,0 };
		DWORD nlen = col * row;
		DWORD nCharacter;
		DWORD color = gettxtColor();
		TextColor(color);
		FillConsoleOutputCharacterA(whandConsole, (TCHAR)ch, nlen, pos, &nCharacter);
	}
	void clrscr(HANDLE hscreen, int col, int row, char ch)
	{
		COORD pos = { 0,0 };
		DWORD nlen = col * row;
		DWORD nCharacter;
		DWORD color = gettxtColor();
		TextColor(color);
		FillConsoleOutputCharacterA(hscreen, (TCHAR)ch, nlen, pos, &nCharacter);
	}
}