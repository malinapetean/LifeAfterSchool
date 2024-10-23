#include "UserEventsList.h"

void UserEventsList::addEventToUserEvents(Event e)
{
	this->userEvents.push_back(e);
}

void UserEventsList::removeEventFromUserEvents(int pos)
{
	this->userEvents.erase(this->userEvents.begin() + pos);
}

vector<Event>& UserEventsList::getUserEvents()
{
	return this->userEvents;
}
