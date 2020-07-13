#ifndef EventMouseOrKey_H
#define EventMouseOrKey_H

#include "console.h"
#include "List.h"
#include "Window.h"
#include <thread>
using namespace scl;
using namespace std;


class EventMouseOrKey :public CompareData<int>
{

public:
	EventMouseOrKey();
	~EventMouseOrKey();
	int getId() override;
	EventMouseOrKey& operator+=(window* handle);
	EventMouseOrKey& operator-=(window* handle);
	bool isLock();
	void unLockControl(window* w);
	void lockControl(window * w);
	node<window>* getActiveControl();
	void ProcessAction(EventConsole& evt);
	void setScreen(HANDLE hscreen);
	HANDLE getScreen();
private:
	static int count;
	static EventMouseOrKey* Instance;
	int _id = 0;
	HANDLE _hscreen;
	List<window>* container;
	bool isMouse(EventConsole& evt) {
		return evt.KeyOrMouse == 1;
	}
	node<window>* controlActive = NULL;
	friend class EventController;
	bool _isLock = false;
};


#endif // !EventMouseOrKey
