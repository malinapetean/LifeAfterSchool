#pragma once
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Event
{
private:
	string title;
	string description;
	tm dateandtime;
	int nr_people;
	string link;
public:
	Event();
	~Event();
	Event(const Event& e);
	Event(const string& title, const string& desc, const tm& date_time, const int& nrPers, const string& link);
	friend bool operator==(const Event& e1, const Event& e2);
	friend ostream& operator<<(ostream& os, const Event& e);
	friend istream& operator>>(istream& is, Event& e);
	string get_title() { return this->title; }
	string get_description() { return this->description; }
	tm get_date_time() { return this->dateandtime; }
	int get_nr_people() { return this->nr_people; }
	string get_link() { return this->link; }
	void set_title(string& title) { this->title = title; }
	void set_description(string& desc) { this->description = desc; }
	void set_date_time(tm& date_time) { this->dateandtime = date_time; }
	void set_nr_people(int& nrPers) { this->nr_people = nrPers; }
	void set_link(string& link) { this->link = link; }
	string tostring();
	

};


