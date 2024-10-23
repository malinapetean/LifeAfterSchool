#pragma once
#include"UserEventsList.h"

class FileUserEventsList : public UserEventsList
{
protected:
	string fileName;
public:
	FileUserEventsList(const string& fileName) : fileName{ fileName }{}
	virtual ~FileUserEventsList() {}
	virtual void writeToFile()=0;
	virtual void displayUserEvents()=0;
};
