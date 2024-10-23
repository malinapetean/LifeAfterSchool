#include"EventValidator.h"

EventException::EventException(vector<string>)
{
	this->errors = errors;
}

vector<string> EventException::getErrors() const
{
	return this->errors;
}

void EventValidator::validate(Event e)
{
	vector<string> errors;
	if (e.get_title().size() < 3)
		errors.push_back("The title must have at least 3 characters\n");
	if (e.get_description().size() < 3)
		errors.push_back("The description must have at least 3 characters\n");
	tm date = e.get_date_time();
	if( date.tm_year < -1900)
		errors.push_back("The year must be a positive number\n");
	if (date.tm_mon < 0 || date.tm_mon > 11)
		errors.push_back("The month must be a number between 1 and 12\n");
	if (date.tm_mday<1 || date.tm_mday>31)
		errors.push_back("The day must be a number between 1 and 31\n");
	if (date.tm_hour < 0 || date.tm_hour>23)
		errors.push_back("The hour must be a number between 0 and 23\n");
	if(e.get_nr_people()<0)
		errors.push_back("The number of people must be a positive number\n");
	size_t poswww = e.get_link().find("www");
	size_t poshttp = e.get_link().find("http");
	if (poswww != 0 && poshttp != 0)
		errors.push_back("The link is not okay\n");
	if (errors.size() > 0)
		throw EventException(errors);


}
