#include "Repository.h"
#include "RepoException.h"
#include <fstream>
#include<iostream>
Repository::Repository(const string& filename)
{
	this->filename = filename;
	this->readFromFile();
}
Repository::~Repository()
{
}
Repository::Repository(const Repository& other)
{
	this->filename = other.filename;
	this->events = other.events;
}

void Repository::addEventRepo(Event e)
{
	this->events.push_back(e);
	this->writeToFile();
}
void Repository::removeEvent(int pos)
{
	this->events.erase(this->events.begin() + pos);
	this->writeToFile();
}
void Repository::updateFile()
{
	this->writeToFile();
}	
int Repository::getSize()
{
	return this->events.size();
}
vector<Event>& Repository::getEvents()
{
	return this->events;
}
void Repository::readFromFile()
{
	ifstream file(this->filename);
	if(!file.is_open())
		throw FileException("The file could not be opened!\n");

	Event e;
	while (file >> e)
	{
		this->events.push_back(e);
	}
	file.close();
}
void Repository::writeToFile()
{
	ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be opened!\n");
	for (auto e : this->events)
		file << e;
	file.close();
}


//User events
//vector<Event>& Repository::getUserEvents()
//{
//	return this->userevents;
//}
//void Repository::addEventToUserEvents(int pos)
//{
//	this->userevents.push_back(this->events[pos]);
//}
//void Repository::removeEventFromUserEvents(int pos)
//{
//	this->userevents.erase(this->userevents.begin()+pos);
//}