#pragma once
#include"Repository.h"
class Action
{
protected:
	Repository& repo;
public:
	//virtual ~Action() = default;
	Action(Repository& repo) : repo{ repo } {}
	virtual void undo() = 0;
	virtual void redo() = 0;

};

class AddAction : public Action
{
private:
	Event event;
	
public:
	AddAction(Repository& repo, Event event) : Action{ repo }, event{ event } {}
	void undo() override
	{
		string title = event.get_title();
		int nr_people = event.get_nr_people();
		int index;
		auto it = find_if(repo.getEvents().begin(),repo.getEvents().end(), [&title, &nr_people](Event& e) {return e.get_title() == title && e.get_nr_people() == nr_people; });
		if (it != repo.getEvents().end())
			 index=distance(repo.getEvents().begin(), it);
		repo.removeEvent(index);
	}
	void redo() override
	{
		repo.addEventRepo(event);
	}
};

class RemoveAction : public Action
{
private:
	Event event;
public:
	RemoveAction(Repository& repo, Event event) : Action{ repo }, event{ event } {}
	void undo() override
	{
		repo.addEventRepo(event);
	}
	void redo() override
	{
		string title = event.get_title();
		int nr_people = event.get_nr_people();
		int index;
		auto it = find_if(repo.getEvents().begin(), repo.getEvents().end(), [&title, &nr_people](Event& e) {return e.get_title() == title && e.get_nr_people() == nr_people; });
		if (it != repo.getEvents().end())
			index = distance(repo.getEvents().begin(), it);
		repo.removeEvent(index);
	}

};

//class UpdateAction : public Action
//{
//private:
//	Event old_event;
//	Event new_event;
//public:
//	UpdateAction(Repository& repo, Event old_event, Event new_event) : Action{ repo }, old_event{ old_event }, new_event{ new_event } {}
//	void undo() override
//	{
//		string title = new_event.get_title();
//		int nr_people = new_event.get_nr_people();
//		int index;
//		auto it = find_if(repo.getEvents().begin(), repo.getEvents().end(), [&title, &nr_people](Event& e) {return e.get_title() == title && e.get_nr_people() == nr_people; });
//		if (it != repo.getEvents().end())
//			index = distance(repo.getEvents().begin(), it);
//		
//	}
//};

