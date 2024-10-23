#pragma once
#include<vector>
#include "Event.h"
class Repository
{
private:
	vector<Event> events;
	string filename;
	void readFromFile();
	void writeToFile();
public:
	/// <summary>
	/// The default constructor of the repository
	/// </summary>
	Repository(const string&);
	Repository(const Repository& other);
	Repository() = default;
	/// <summary>
	/// The destructor of the repository
	/// </summary>
	~Repository();
	/// <summary>
	/// The function adds an event to the repository
	/// </summary>
	/// <param name="e"></param> The event to be added
	void addEventRepo(Event e);
	/// <summary>
	/// The function removes an event from the repository
	/// </summary>
	/// <param name="pos"></param> The position of the event to be removed
	void removeEvent(int pos);
	void updateFile();
	/// <summary>
	/// The function returns the size of the repository
	/// </summary>
	/// <returns></returns> The size of the repository
	int getSize();
	/// <summary>
	/// The function returns the events from the repository
	/// </summary>
	/// <returns></returns> The events from the repository
	vector<Event>& getEvents();
	/// <summary>
	/// This function returns the events that the user has
	/// </summary>
	/// <returns></returns> The events that the user has
	
};