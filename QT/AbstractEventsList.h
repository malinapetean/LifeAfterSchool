#pragma once
#include "Event.h"
#include <vector>
class AbstractEventsList
{
public:
	virtual void write() = 0;
	virtual void open() = 0;
	virtual void set_data(vector<Event> events) = 0;
	virtual ~AbstractEventsList()=default;
};

