#include "EventMouseOrKey.h"
#include "console.h"

EventMouseOrKey::EventMouseOrKey()
{
	container = new List<window>;
	_id = EventMouseOrKey::count++;
}

EventMouseOrKey::~EventMouseOrKey()
{
	delete container;
}

int EventMouseOrKey::getId()
{
	return _id;
}

EventMouseOrKey& EventMouseOrKey::operator+=(window* handle)
{
	container->insertlast(handle);
	return *this;
}

EventMouseOrKey& EventMouseOrKey::operator-=(window* handle)
{
	container->DelCen(handle);
	return *this;
}
bool EventMouseOrKey::isLock()
{
	return _isLock;
}
void EventMouseOrKey::unLockControl(window* w)
{
	controlActive = NULL;
	_isLock = false;
}
void EventMouseOrKey::lockControl(window* w)
{
	controlActive = container->search(w);
	_isLock = true;
}
node<window>* EventMouseOrKey::getActiveControl()
{
	return controlActive;
}
void EventMouseOrKey::ProcessAction(EventConsole& evt)
{
	if (controlActive != NULL && (evt.isKeyEvent() || evt._Smouse._kindMouse == MouseKind::left)) {
		controlActive->info->action(evt);
	}
}
void EventMouseOrKey::setScreen(HANDLE hscreen)
{
	_hscreen = hscreen;
}
HANDLE EventMouseOrKey::getScreen()
{
	return _hscreen;
}
int EventMouseOrKey::count = 0;