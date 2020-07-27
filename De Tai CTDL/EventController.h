#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H
#include "EventMouseOrKey.h"
class EventController
{
public:
	EventController();
	~EventController();
	EventController& operator+=(EventMouseOrKey* handle);
	EventController& operator-=(EventMouseOrKey* handle);
	static EventController* getInstance();

	HANDLE getScreenActive() {
		return _container.getfirst()->info->getScreen();
	}
	void setIdLock(bool isLock);
	void Process(EventController* handle);
	void Stop();
	thread* Start();
private:
	static EventController* Instance;
	List<EventMouseOrKey> _container;
	bool isStop = false;
	bool _isLock = false;
};


#endif // !EVENTCONTROLLER_H
