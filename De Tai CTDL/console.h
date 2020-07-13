// basic console functions, collected by Nguyen trong tai

#ifndef _console_header
#define _console_header

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
//--------------------------------------------------------


#define ColorCode_Back			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define default_ColorCode		7


#define key_Up		1072
#define key_Down	1080
#define key_Left	1075
#define key_Right	1077
#define key_Enter   13
#define key_none	-1
#define key_bkspace 8
#define key_tab		9


namespace scl {

#define color_black 0x0000
#define color_darkblue 0x0001
#define color_darkgreen 0x0002
#define color_darkcyan 0x0003
#define color_darkred 0x0004
#define color_darkpink 0x0005
#define color_darkyellow 0x0006
#define color_darkwhite 0x0007
#define color_grey 0x0008
#define color_blue 0x0009
#define color_green 0x000a
#define color_cyan 0x000b
#define color_red 0x000c
#define color_pink 0x000d
#define color_yellow 0x000e
#define color_white 0x000f

#define colorbk_black 0x0000
#define colorbk_darkblue 0x0010
#define colorbk_darkgreen 0x0020
#define colorbk_darkcyan 0x0030
#define colorbk_darkred 0x0040
#define colorbk_darkpink 0x0050
#define colorbk_darkyellow 0x0060
#define colorbk_darkwhite 0x0070
#define colorbk_grey 0x0080
#define colorbk_blue 0x0090
#define colorbk_green 0x00a0
#define colorbk_cyan 0x00b0
#define colorbk_red 0x00c0
#define colorbk_pink 0x00d0
#define colorbk_yellow 0x00e0
#define colorbk_white 0x00f0


	void DisableMaxiMize(LPCSTR title);
	void SetTitle(std::string title);

	void SizeConsole(SHORT Width, SHORT height);
	void SizeConsole(HANDLE hscreen, SHORT Width, SHORT height);

	void SizeBuffer(SHORT col, SHORT row);
	void WriteChar(char ch, SHORT x, SHORT y, SHORT color);
	HANDLE CreateScreenBuff();
	void DeleteScreenBuff(HANDLE hscreen);

	CHAR_INFO* GetScreenCurrent();

	void WriteBlockChar(
		char* Arraych,
		SHORT row, SHORT col,
		SHORT x, SHORT y,
		int color);
	void WriteBlockChar(HANDLE hscreen, CHAR_INFO* charater,
		SHORT row, SHORT col,
		SHORT x, SHORT y);
	void WriteBlockChar(CHAR_INFO* charater,
		SHORT row, SHORT col,
		SHORT x, SHORT y);
	void ReadBlockChar(
		char* Arraych,
		SHORT row, SHORT col,
		SHORT x, SHORT y);
	void ReadBlockChar(HANDLE hscreen, CHAR_INFO* charater,
		SHORT row, SHORT col,
		SHORT x, SHORT y);
	void ReadBlockChar(CHAR_INFO* charater,
		SHORT row, SHORT col,
		SHORT x, SHORT y);
	void fillBackGround(int col, int row, int color);
	void fillBackGround(HANDLE hscreen, int col, int row, int color);
	enum MouseKind
	{
		none, left, right, dleft, move
	};
	struct  StatusMouse
	{

		MouseKind _kindMouse;
		int  x = 0, y = 0;
		StatusMouse(int X, int Y, MouseKind kind) {
			x = X;
			y = Y;
			_kindMouse = kind;
		}
		StatusMouse() { _kindMouse = MouseKind::none; x = 0; y = 0; };
	};

	struct EventConsole
	{
		bool KeyOrMouse = 0;
		StatusMouse _Smouse;
		int _key = -1;
		void reset() {
			KeyOrMouse = 0;
			_key = -1;
			_Smouse._kindMouse = MouseKind::none;
		}
		bool isKeyEvent() {
			return KeyOrMouse == 0;
		}
		bool isMouseEvent() {
			return KeyOrMouse == 1;
		}
	};
	//--------------------------------------------------------

	int inputKey();

	//-------------------------Screen-------------------------
	void clrscr();

	//screen: goto [x,y]
	void gotoXY(int column, int line);
	//screen: goto [x,y]
	void gotoXY(HANDLE hscreen, int column, int line);
	//screen: get [x]
	int whereX();

	//screen: get [y]
	int whereY();
	int gettxtColor();
	int gettxtColor(HANDLE hscreen);

	void TextColor(int color);
	void TextColor(HANDLE hscreen, int color);
	//end----------------------Screen----------------------end
	void ShowCur(bool CursorVisibility);
	void ShowCur(HANDLE hscreen, bool CursorVisibility);
	//catch key anh mouse
	void KeyMouse(EventConsole* eventcon);
	//------------------------
	void clrscr(int col, int row, char ch);
	void clrscr(HANDLE hscreen, int col, int row, char ch);
}
//-------------------------
#endif