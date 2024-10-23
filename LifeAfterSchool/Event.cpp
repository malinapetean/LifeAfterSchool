#include "Event.h"
#include <sstream>
#include <vector>


Event::Event(const string& title, const string& desc, const tm& date_time, const int& nrPers, const string& link)
{
	this->title = title;
	this->description = desc;
	this->dateandtime = date_time;
	this->nr_people = nrPers;
	this->link = link;
}


Event::Event()
{
	title = "";
	description = "";
	nr_people = 0;
	link = "";
	dateandtime = tm();
}
Event::Event(const Event& e)
{
	this->title = e.title;
	this->description = e.description;
	this->dateandtime = e.dateandtime;
	this->nr_people = e.nr_people;
	this->link = e.link;
}
Event::~Event()
{
}

bool operator==(const Event& e1, const Event& e2)
{
	if (e1.title == e2.title && e1.nr_people == e2.nr_people)
		return true;
	return false;
}

ostream& operator<<(ostream& os, const Event& event)
{
    os << '\"' << event.title << "\"," << '\"' << event.description << "\"," << std::put_time(&event.dateandtime, "%d/%m/%Y %H:%M") << "," << event.nr_people << "," << '\"' << event.link << "\"\n";
	return os;
}

istream& operator>>(istream& is, Event& e)
{
    string line;
    getline(is, line);
    vector<string> tokens;
    int i = 0;
    string token;
    while (i < line.size())
    {
        if (line[i] == '"')
        {
            i++;
            while (line[i] != '"' && i < line.size())
            {
                token += line[i];
                i++;
            }
            i += 2;
            tokens.push_back(token);
            token.clear();
        }
        else
        {
            while (line[i] != ',' && i < line.size())
            {
                token += line[i];
                i++;
            }
            i++;
            tokens.push_back(token);
            token.clear();
        }


    }
    if (tokens.size() != 5)
        return is;
    e.title = tokens[0];
    e.description = tokens[1];
    stringstream ss2(tokens[2]);
    ss2 >> get_time(&e.dateandtime, "%d/%m/%Y %H:%M");
    e.nr_people = stoi(tokens[3]);
    e.link = tokens[4];
    return is;
}



string Event::tostring(){
	string str = "";
	stringstream s;
	s << put_time(&this->dateandtime, "%d/%m/%Y %H:%M");

	str +=this->title + "\n" + this->description + "\n" + s.str() + "\n" + to_string(this->nr_people) + "\n" + this->link+ "\n";
	return str;
}


