#include "CSVFileUserEvents.h"
#include <fstream>
#include "repoException.h"
#include <cstdlib>


void CSVFileUserEventsList::writeToFile()
{
	ofstream f(this->fileName);
	if (!f.is_open())
		throw FileException("The file could not be opened!");
	for (auto e : this->userEvents)
		f << e;
	f.close();
}
void CSVFileUserEventsList::displayUserEvents()
{
	string aux = this->fileName;
	string command = "start "+ aux;
	system(command.c_str());
}
