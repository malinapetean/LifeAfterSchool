#pragma once
#include <string>
#include <vector>
#include "Event.h"

class EventException
{
private: 	
	vector<string> errors;
public:
	EventException(vector<string>);
	vector<string> getErrors() const;
	
};

class EventValidator {
public:
	EventValidator(){}
	static void validate(Event);
};