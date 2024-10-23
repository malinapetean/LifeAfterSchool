#pragma once
#include"fileUserEventsList.h"

class CSVFileUserEventsList : public FileUserEventsList
{
public:
	CSVFileUserEventsList(const string& fileName) : FileUserEventsList{ fileName } {}
	~CSVFileUserEventsList() {}
	void writeToFile() override;
	void displayUserEvents() override;
};
