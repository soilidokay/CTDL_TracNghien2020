#include "Window.h"

#include "EventMouseOrKey.h"


window::window(int width, int height, int x, int y)
{
	_area = nullptr;
	_height = height;
	_width = width;
	_x = x;
	_y = y;
	_color = color_red;
	_select = -1;
}

window::~window()
{

}

void window::SetScreen(HANDLE hscreen)
{
	_hScreen = hscreen;
}
