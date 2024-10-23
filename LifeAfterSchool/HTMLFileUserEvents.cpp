#include "HTMLFileUserEvents.h"
#include"RepoException.h"
#include <fstream>
#include<cstdlib>

void HTMLFileUserEventsList::writeToFile()
{
	ofstream f(this->fileName);
	if (!f.is_open())
		throw FileException("The file could not be opened!");
	f << "<!DOCTYPE html>\n";
	f << "<html>\n";
	f << "<head>\n";
	f << "<title>User Events</title>\n";
	f << "</head>\n";
	f << "<body>\n";
	f << "<table border=\"1\">\n";
	f << "<tr>\n";
	f << "<td>Title</td>\n";
	f << "<td>Description</td>\n";
	f << "<td>Type</td>\n";
	f << "<td>Time</td>\n";
	f << "<td>Organizer</td>\n";
	f << "</tr>\n";
	for (auto e : this->userEvents)
	{
		f << "<tr>\n";
		f << "<td>" << e.get_title() << "</td>\n";
		f << "<td>" << e.get_description() << "</td>\n";
		tm dateAndTime = e.get_date_time();
		f << "<td>" << put_time(&dateAndTime, "%d/%m/%Y %H:%M") << "</td>\n";
		f << "<td>" << e.get_nr_people() << "</td>\n";
		f << "<td><a href=\"" << e.get_link() << "\">Link</a></td>\n";
		f << "</tr>\n";
	}
	f << "</table>\n";
	f << "</body>\n";
	f << "</html>\n";
	f.close();
}

void HTMLFileUserEventsList::displayUserEvents()
{
	string aux = this->fileName;
	aux = "start " + aux;
	system(aux.c_str());
}
