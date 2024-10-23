#pragma once
#include "fileUserEventsList.h"

class HTMLFileUserEventsList : public FileUserEventsList
{
public:
	HTMLFileUserEventsList(const string& fileName) : FileUserEventsList{ fileName } {}
	~HTMLFileUserEventsList() {}
	void writeToFile() override;
	void displayUserEvents() override;
};
