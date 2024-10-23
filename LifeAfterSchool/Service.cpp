#include "Service.h"
#include <algorithm>
#include <iostream>
#include <sstream>




Service::Service(Repository repository, FileUserEventsList* userdata)
{
	this->repo = repository;
	this->userEvents = userdata;
}

Service::~Service()
{
}
vector<Event>& Service::getEvents()
{
	return this->repo.getEvents();
}
Event& Service::getEvent(int pos)
{
	return this->repo.getEvents()[pos];
}
int Service::nrEvents()
{
	return this->repo.getSize();
}
int Service::searchEvent(string& title, int& nr_people)
{
	auto it = find_if(getEvents().begin(), getEvents().end(), [&title, &nr_people](Event& e) {return e.get_title() == title && e.get_nr_people() == nr_people; });
	if (it != getEvents().end())
		return distance(getEvents().begin(), it);
	return -1;
}

void Service::addEventService(string& title, string& desc, tm& date_time, int& nrPers, string& link)
{
	Event e = Event(title, desc, date_time, nrPers, link);
	try {
		this->validator.validate(e);
	}
	catch (EventException& ex)
	{
		string errors = "";
		for (auto err : ex.getErrors())
			errors += err;
		throw RepositoryException(errors);

	}

	if (searchEvent(title, nrPers) != -1)
		throw RepositoryException("The event already exists\n");
	this->repo.addEventRepo(e);


	redoActions.clear(); 
	Action* action = new AddAction(this->repo, e);
	this->undoActions.push_back(move(action));

}

void Service::removeEventService(string title, int nr_people)
{
	int index = searchEvent(title, nr_people);
	if (index != -1)
	{
		Event e = this->getEvent(index);
		this->repo.removeEvent(index);
		redoActions.clear(); 
		Action* action = new RemoveAction(this->repo,e); 
		this->undoActions.push_back(move(action)); 
	}	
	else
		throw RepositoryException("The event does not exist\n");
}

//1-update was made
//0-event is not valid
//-1-event does not exist
//2-updated event already exists
void Service::updateEvent(string& newtitle, string& newdesc, tm& newdate_time, int& newnrPers, string& newlink, string& title, int& nrPers)
{
	int ie = searchEvent(title, nrPers);
	if (ie == -1)
		throw RepositoryException("The event does not exist\n");
	Event updatedEvent = Event(newtitle, newdesc, newdate_time, newnrPers, newlink);
	this->validator.validate(updatedEvent);
	if (searchEvent(newtitle, newnrPers) != -1)
		throw RepositoryException("The updated event already exists\n");
	Event& e = this->getEvent(ie);
	e.set_title(newtitle);
	e.set_description(newdesc);
	e.set_date_time(newdate_time);
	e.set_nr_people(newnrPers);
	e.set_link(newlink);
	this->repo.updateFile();
}
void Service::set_date_time(tm& date_time, int year, int month, int day, int hour, int minute)
{
	date_time.tm_year = year - 1900;
	date_time.tm_mon = month - 1;
	date_time.tm_mday = day;
	date_time.tm_hour = hour;
	date_time.tm_min = minute;
}
int Service::checkValidEvent(const string& title, const string& desc, const tm& date_time, const int& nrPers, const string& link)
{
	if (title.length() == 0 || desc.length() == 0
		|| date_time.tm_mday < 1 || date_time.tm_mday > 31
		|| date_time.tm_mon + 1 < 1 || date_time.tm_mon > 12
		|| date_time.tm_year + 1900 < 0
		|| date_time.tm_hour < 0 || date_time.tm_hour >24
		|| date_time.tm_min < 0 || date_time.tm_min > 59
		|| nrPers < 0 || link.length() == 0)
		return 0;
	return 1;
}
void Service::addEventToUserList(string& eventtitle, int& nrPers)
{
	auto it = find_if(getUserEvents().begin(), getUserEvents().end(), [&eventtitle, &nrPers](Event& e) {return e.get_title() == eventtitle && e.get_nr_people() == nrPers; });
	if (it != getUserEvents().end())
		throw RepositoryException("The event already exists in the user list\n");
	int i = searchEvent(eventtitle, nrPers);
	Event etoadd= this->getEvent(i);
	int nr = etoadd.get_nr_people() + 1;
	etoadd.set_nr_people(nr);
	this->userEvents->addEventToUserEvents(etoadd);
	this->userEvents->writeToFile();

}
void Service::removeEventFromUserList(string& eventTitle, int& nrPers)
{
	
	auto it = find_if(getUserEvents().begin(), getUserEvents().end(), [&eventTitle, &nrPers](Event& e) {return e.get_title() == eventTitle && e.get_nr_people() == nrPers; });
	if (it != getUserEvents().end())
	{
		nrPers = it->get_nr_people() - 1;
		int i = searchEvent(eventTitle, nrPers);
		int intextodelete = distance(getUserEvents().begin(), it);
		this->userEvents->removeEventFromUserEvents(intextodelete);
		this->userEvents->writeToFile();
	}
	else
		throw RepositoryException("The event does not exist in the user list\n");

}
vector<Event>& Service::getUserEvents()
{
	return this->userEvents->getUserEvents();
}
Event& Service::getUserEvent(int pos)
{
	return this->userEvents->getUserEvents()[pos];
}
bool Service::compareDates(tm date_time1, tm date_time2)
{
	if (date_time1.tm_year > date_time2.tm_year)
		return true;
	else if (date_time1.tm_year == date_time2.tm_year)
	{
		if (date_time1.tm_mon > date_time2.tm_mon)
			return true;
		else if (date_time1.tm_mon == date_time2.tm_mon)
		{
			if (date_time1.tm_mday > date_time2.tm_mday)
				return true;
			else if (date_time1.tm_mday == date_time2.tm_mday)
			{
				if (date_time1.tm_hour > date_time2.tm_hour)
					return true;
				else if (date_time1.tm_hour == date_time2.tm_hour)
				{
					if (date_time1.tm_min > date_time2.tm_min)
						return true;
				}
			}
		}
	}
	return false;
}
void Service::sortEvents_month(int month, vector<Event>& events_orderd)
{
	//return all events for a given month, orderd by date and time, month is int between 1 and 12 if month=0 then return all
	//events
	for(auto e: getEvents())
	{
		if (month == 0)
		{
			events_orderd.push_back(e);
		}
		else if (e.get_date_time().tm_mon + 1 == month)
		{
			events_orderd.push_back(e);
		}
	}

	auto compare = [this](Event& e1, Event& e2)
		{return !compareDates(e1.get_date_time(), e2.get_date_time()); };
	sort(events_orderd.begin(), events_orderd.end(), compare);


}

void Service::displayUserEvents()
{
	this->userEvents->displayUserEvents();
}

tm Service::convertStringToTime(const string date)
{
	tm time = {};
	istringstream ss(date);
	ss >> get_time(&time, "%d/%m/%Y %H:%M");
	return time;

}

void Service::undo()
{
	if(this->undoActions.empty()) 
	{
		throw RepositoryException("No more undos\n"); 
	}
	auto a = move(this->undoActions[this->undoActions.size() - 1]); 
	this->undoActions.pop_back(); 
	a->undo();

	redoActions.push_back(move(a));
}

void Service::redo()
{
	if(this->redoActions.empty())  
	{
		throw RepositoryException("No more redos\n");  
	}
	auto a = move(this->redoActions[this->redoActions.size() - 1]);
	this->redoActions.pop_back();
	a->redo(); 

	undoActions.push_back(move(a)); 
}




//void Service::addtenEvents()
//{
//	tm date_time;
//	set_date_time(date_time, 2024, 4, 6, 16, 00);
//	Event newEvwnt1(string("Focus in the park 2024 party"), string("Muzeul National Brukental Sibiu"), date_time, 100, string("https://www.facebook.com/events/739433798296202/?ref=newsfeed"));
//	this->repo.addEventRepo(newEvwnt1);
//	//this->repo.addEvent(Event("Focus in the park 2024 party", "Muzeul National Brukental Sibiu", date_time, 100, "https://www.facebook.com/events/739433798296202/?ref=newsfeed"));
//
//	set_date_time(date_time, 2024, 4, 4, 22, 30);
//	Event newEvwnt2(string("Lasa-ma papa la bal!"), string("Euhoria Music Hall"), date_time, 200, string("https://www.facebook.com/events/369095659371711?ref=newsfeed"));
//	this->repo.addEventRepo(newEvwnt2);
//	//this->repo.addEvent(Event("Lasa-ma papa la bal!", "Euhoria Music Hall", date_time, 200, "https://www.facebook.com/events/369095659371711?ref=newsfeed"));
//
//	set_date_time(date_time, 2024, 4, 11, 23, 00);
//	Event newEvwnt3(string("Law party"), string("Euhoria Music Hall"), date_time, 150, string("https://www.facebook.com/events/1442309573376203/?acontext=%7B%22event_action_history%22%3A[%7B%22mechanism%22%3A%22discovery_top_tab%22%2C%22surface%22%3A%22bookmark%22%7D]%2C%22ref_notif_type%22%3Anull%7D"));
//	this->repo.addEventRepo(newEvwnt3);
//	//this->repo.addEvent(Event("Law party", "Euhoria Music Hall", date_time, 150, "https://www.facebook.com/events/1442309573376203/?acontext=%7B%22event_action_history%22%3A[%7B%22mechanism%22%3A%22discovery_top_tab%22%2C%22surface%22%3A%22bookmark%22%7D]%2C%22ref_notif_type%22%3Anull%7D"));
//
//	set_date_time(date_time, 2024, 5, 30, 00, 00);
//	Event newEvwnt4(string("Zilele Clujului"), string("Cluj Napoca"), date_time, 125, string("https://www.facebook.com/events/302635949195759?acontext=%7B%22event_action_history%22%3A[%7B%22surface%22%3A%22home%22%7D%2C%7B%22mechanism%22%3A%22discovery_top_tab%22%2C%22surface%22%3A%22bookmark%22%7D]%2C%22ref_notif_type%22%3Anull%7D"));
//	this->repo.addEventRepo(newEvwnt4);
//	//this->repo.addEvent(Event("Zilele Clujului", "Cluj Napoca", date_time, 125, "https://www.facebook.com/events/302635949195759?acontext=%7B%22event_action_history%22%3A[%7B%22surface%22%3A%22home%22%7D%2C%7B%22mechanism%22%3A%22discovery_top_tab%22%2C%22surface%22%3A%22bookmark%22%7D]%2C%22ref_notif_type%22%3Anull%7D"));
//
//	set_date_time(date_time, 2024, 4, 11, 22, 00);
//	Event newEvwnt5(string("/form university party"), string("form"), date_time, 100, string("https://www.facebook.com/events/760102306263086/?acontext=%7B%22event_action_history%22%3A[%7B%22mechanism%22%3A%22search_results%22%2C%22surface%22%3A%22bookmark_search%22%7D]%2C%22ref_notif_type%22%3Anull%7D"));
//	this->repo.addEventRepo(newEvwnt5);
//	//this->repo.addEvent(Event("/form university party", "form", date_time, 100, "https://www.facebook.com/events/760102306263086/?acontext=%7B%22event_action_history%22%3A[%7B%22mechanism%22%3A%22search_results%22%2C%22surface%22%3A%22bookmark_search%22%7D]%2C%22ref_notif_type%22%3Anull%7D"));
//
//	set_date_time(date_time, 2024, 4, 19, 21, 00);
//	Event newEvwnt6(string("Bachata-Reggaeton Party"), string("Club NOA"), date_time, 50, string("https://www.facebook.com/events/393908426705225/?acontext=%7B%22event_action_history%22%3A[%7B%22mechanism%22%3A%22search_results%22%2C%22surface%22%3A%22bookmark_search%22%7D]%2C%22ref_notif_type%22%3Anull%7D"));
//	this->repo.addEventRepo(newEvwnt6);
//	//this->repo.addEvent(Event("Bachata-Reggaeton Party", "Club NOA", date_time, 50, "https://www.facebook.com/events/393908426705225/?acontext=%7B%22event_action_history%22%3A[%7B%22mechanism%22%3A%22search_results%22%2C%22surface%22%3A%22bookmark_search%22%7D]%2C%22ref_notif_type%22%3Anull%7D"));
//
//	set_date_time(date_time, 2024, 4, 19, 21, 59);
//	Event newEvwnt7(string("Dimitri Vegas"), string("BTarena Cluj-Napoca"), date_time, 170, string("https://www.facebook.com/events/1355678528469975/?acontext=%7B%22event_action_history%22%3A[%7B%22mechanism%22%3A%22search_results%22%2C%22surface%22%3A%22bookmark_search%22%7D]%2C%22ref_notif_type%22%3Anull%7D"));
//	this->repo.addEventRepo(newEvwnt7);
//	//this->repo.addEvent(Event("Dimitri Vegas", "BTarena Cluj-Napoca", date_time, 170, "https://www.facebook.com/events/1355678528469975/?acontext=%7B%22event_action_history%22%3A[%7B%22mechanism%22%3A%22search_results%22%2C%22surface%22%3A%22bookmark_search%22%7D]%2C%22ref_notif_type%22%3Anull%7D"));
//
//}