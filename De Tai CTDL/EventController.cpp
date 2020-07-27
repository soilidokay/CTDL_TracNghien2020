#include"EventController.h"

EventController::EventController()
{
}

EventController::~EventController()
{
}
EventController& EventController::operator+=(EventMouseOrKey* handle)
{
	// TODO: insert return statement here
	_container.insertfirst(handle);
	return *this;
}
EventController& EventController::operator-=(EventMouseOrKey* handle)
{
	// TODO: insert return statement here
	_container.DelCen(handle);
	return *this;
}
EventController* EventController::getInstance()
{
	if (Instance == nullptr) {
		Instance = new EventController();
	}
	return Instance;
}
void EventController::setIdLock(bool isLock)
{
	_isLock = isLock;
}
void EventController::Process(EventController* handleOwn)
{

	EventConsole evt;
	do {
		if (_isLock) {
			continue;
		}
		KeyMouse(&evt);
		if (_isLock) {
			Sleep(2000);
			continue;
		}
		if (handleOwn->_container.isempty()) continue;

		EventMouseOrKey* handle = handleOwn->_container.getfirst()->info;

		if (handle->isLock()) {
			handle->ProcessAction(evt);
			continue;
		}

		if (handle->container->isempty()) continue;

		node<window>* trav = handle->container->getfirst();

		if (evt._key == key_tab && handle->controlActive != NULL) {
			handle->controlActive->info->SetActive(false);

			handle->controlActive = handle->controlActive->next == NULL
				? handle->container->getfirst()
				: handle->controlActive->next;

			if (handle->controlActive != NULL) {
				handle->controlActive->info->SetActive(true);
			}

			continue;
		}


		if (evt.isMouseEvent() && evt._Smouse._kindMouse != MouseKind::none) {

			while (trav != NULL) {
				if (trav->info->checkACtive(evt._Smouse)) {
					if (handle->controlActive != NULL) {
						handle->controlActive->info->SetActive(false);
					}

					handle->controlActive = trav;
					handle->controlActive->info->SetActive(true);

					break;
				}
				trav = trav->next;
			}

			if (trav == NULL) {
				if (handle->controlActive != NULL) {
					handle->controlActive->info->SetActive(false);
				}
				handle->controlActive = NULL;
			}
		}


		handle->ProcessAction(evt);
		

	} while (!isStop);

}
void EventController::Stop()
{
	isStop = true;
}
thread* EventController::Start()
{
	return new thread{ [this] { this->Process(this); } };
}
EventController* EventController::Instance = nullptr;