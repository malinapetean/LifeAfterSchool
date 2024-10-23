#pragma once
#include "Event.h"
#include <vector>

class UserEventsList
{
protected:
	vector<Event> userEvents;
public:
	void addEventToUserEvents(Event e);
	void removeEventFromUserEvents(int pos);
	vector<Event>& getUserEvents();

};
