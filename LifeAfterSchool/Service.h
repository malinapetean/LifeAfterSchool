#pragma once
#include"Repository.h"
#include"FileUserEventsList.h"
#include"EventValidator.h"
#include"RepoException.h"
#include"Action.h"
#include<algorithm>
#include<ctime>
#include<chrono>


class Service
{
private:
	Repository repo;
	FileUserEventsList * userEvents;
	EventValidator validator;
	vector<Action*> undoActions;
	vector<Action*> redoActions;
public:
	/// <summary>
	/// The default constructor of the service
	/// </summary>
	Service(Repository repository, FileUserEventsList* userdata);
	/// <summary>
	/// The destructor of the service
	/// </summary>
	~Service();
	/// <summary>
	/// The function adds an event to the repository
	/// </summary>
	/// <param name="title"></param> The title of the event
	/// <param name="desc"></param> The description of the event
	/// <param name="date_time"></param> The date and time of the event
	/// <param name="nrPers"></param> The number of people that will attend the event
	/// <param name="link"></param>	The link to the event
	/// <returns></returns> 1 if the event was added, 0 if the event is not valid, -1 if the event already exists
	void addEventService(string& title, string& desc, tm& date_time, int& nrPers, string& link);
	/// <summary>
	/// The function removes an event from the repository
	/// </summary>
	/// <param name=""></param> The title of the event
	/// <param name="pos"></param> The position of the event in the repository
	/// <returns></returns>	1 if the event was removed, 0 if the event does not exist
	void removeEventService(string, int pos);
	/// <summary>
	/// The function searches for an event in the repository
	/// </summary>
	/// <param name="title"></param> The title of the event
	/// <param name=""></param> The number of people that will attend the event
	/// <returns></returns> The position of the event in the repository
	int searchEvent(string& title, int&);
	/// <summary>
	/// The function updates an event
	/// </summary>
	/// <param name="newtitle"></param> The new title of the event
	/// <param name="newdesc"></param> The new description of the event
	/// <param name="newdate_time"></param> The new date and time of the event
	/// <param name="newnrPers"></param> The new number of people
	/// <param name="newlink"></param> The new number of people
	/// <param name="title"></param> The title of the event that you want to update
	/// <param name="nrPers"></param> The number of people from the event you want to update
	/// <returns></returns>
	void updateEvent(string& newtitle, string& newdesc, tm& newdate_time, int& newnrPers, string& newlink, string& title, int& nrPers);
	/// <summary>
	/// This function gives the list with all the events
	/// </summary>
	/// <returns></returns> The list of the events
	vector<Event>& getEvents();
	/// <summary>
	/// This function gives an event from a position
	/// </summary>
	/// <param name="pos"></param> The position of the event
	/// <returns></returns> The event from the position
	Event& getEvent(int pos);
	/// <summary>
	/// This function gives the number of the events
	/// </summary>
	/// <returns></returns> the number of the events
	int nrEvents();
	/// <summary>
	/// This function adds 10 events to the aplication
	/// </summary>
	//void addtenEvents();
	/// <summary>
	/// This function sets the date and time of an event
	/// </summary>
	/// <param name="date_time"></param> The date and time of the event
	/// <param name="year"></param>	The year of the event
	/// <param name="month"></param> The month of the event
	/// <param name="day"></param> The day of the event
	/// <param name="hour"></param>	The hour of the event
	/// <param name="minute"></param> The minute of the event
	void set_date_time(tm& date_time, int year, int month, int day, int hour, int minute);
	/// <summary>
	/// This function checks if an event is valid
	/// </summary>
	/// <param name="title"></param> The title of the event
	/// <param name="desc"></param> The description of the event
	/// <param name="date_time"></param> The date and time of the event
	/// <param name="nrPers"></param> The number of people that will attend the event
	/// <param name="link"></param> The link to the event
	/// <returns></returns>	1 if the event is valid, 0 if the event is not valid
	int checkValidEvent(const string& title, const string& desc, const tm& date_time, const int& nrPers, const string& link);
	/// <summary>
	/// This function adds an event to the user events
	/// </summary>
	/// <param name=""></param> The title of the event
	/// <param name="nr"></param> The number of people that will attend the event
	/// <returns></returns> 1 if the event was added, 0 if the event is not valid, -1 if the event already exists
	/// <summary>
	/// This function removes an event from the user events
	/// </summary>
	/// <param name=""></param> The title of the event
	/// <param name="nr"></param> The number of people that will attend the event
	/// <returns></returns> 1 if the event was removed, 0 if the event does not exist
	void addEventToUserList(string& title, int& nrPers);
	void removeEventFromUserList(string&, int& nr);
	/// <summary>
	/// This function gives the list with all the user events
	/// </summary>
	/// <returns></returns> The list of the user events
	vector<Event>& getUserEvents();
	/// <summary>
	/// This function gives the event from a position
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	Event& getUserEvent(int pos);
	static bool compareDates(tm date_time1, tm date_time2);
	void sortEvents_month(int, vector<Event>&);
	void displayUserEvents();
	tm convertStringToTime(const string date);
	void undo();
	void redo();


};
