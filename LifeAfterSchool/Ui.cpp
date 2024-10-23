#include "Ui.h"

Ui::Ui(Service s)
{
	this->serv = s;
}

void Ui::menu()
{
	cout << "1. Admin mode" << endl;
	cout << "2. User mode" << endl;
	cout << "0. Exit" << endl;
	cout << "Choose mode: ";
}

void Ui::adminMenu()
{
	cout << "1. Add event" << endl;
	cout << "2. Remove event" << endl;
	cout << "3. Update event" << endl;
	cout << "4. Show all events" << endl;
	cout << "5. Back" << endl;
	cout << "Choose option: ";
}
void Ui::readEvent(string& title, string& desc, tm& date_time, int& nrPers, string& link)
{
	int day = 0, month = 0, year = 0, hour = 0, minute = 0;
	cout << "Title: ";
	flushStdin();
	getline(cin, title);
	cout << "Description: ";
	getline(cin, desc);
	cout << "Date( dd/mm/yyyy): " << endl;
	cout << "\tDay: ";
	cin >> day;
	flushStdin();
	cout << "\tMonth: ";
	cin >> month;
	flushStdin();
	cout << "\tYear: ";
	cin >> year;
	flushStdin();
	cout << "Time( hh:mm): " << endl;
	cout << "\tHour: ";
	cin >> hour;
	flushStdin();
	cout << "\tMinute: ";
	cin >> minute;
	flushStdin();
	cout << "Number of people: ";
	cin >> nrPers;
	flushStdin();
	cout << "Link: ";
	getline(cin, link);
	date_time.tm_mday = day;
	date_time.tm_mon = month - 1;
	date_time.tm_year = year - 1900;
	date_time.tm_hour = hour;
	date_time.tm_min = minute;
}

void Ui::flushStdin()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Ui::userMenu()
{
	cout << "1. See the events for a given month, one by one\n";
	cout << "2. Delete the event from your list\n";
	cout << "3. Display your list of events\n";
	cout << "4. Back\n";
	cout << "Choose option: ";
}
void Ui::seconduserMenu()
{
	cout << "1. Add current event to your list\n";
	cout << "2. Next\n";
	cout << "3. Stop\n";
	cout << "Choose option: ";
}

void Ui::dispalyEvent(Event& e)
{
	string lines(50, '-');
	cout << lines << endl;
	cout << "Title: " << e.get_title() << endl;
	cout << "Description: " << e.get_description() << endl;
	tm date_time = e.get_date_time();
	cout << "Date and time: " << put_time(&date_time, "%d/%m/%Y %H:%M") << endl;
	cout << "Number of people: " << e.get_nr_people() << endl;
	cout << "Link: " << e.get_link() << endl;
	cout << lines << endl;
}


void Ui::start()
{
	int option;
	cout << "Welcome to the event manager!" << endl;
	///this->serv.addtenEvents();
	do
	{
		option = -1;
		menu();
		cin >> option;
		if (cin.fail()) {
			flushStdin();
			option = -1;
		}
		switch (option)
		{
		case 1:
		{
			do {
				option = -1;
				adminMenu();
				cin >> option;
				if (cin.fail()) {
					flushStdin();
					option = -1;
				}
				string title = "", desc = "", link = "";
				int nr_people = -1;
				tm date_time = { 0 };
				switch (option) {
				case 1:
				{
					cout << "Provide the following in order to add an event:" << endl;
					readEvent(title, desc, date_time, nr_people, link);
					try {
						this->serv.addEventService(title, desc, date_time, nr_people, link);
						cout<<"Event added successfully!"<<endl;
					}
					catch (RepositoryException& e) {
						cout << e.what() << endl;
					}
					catch (EventException& e) {
						for (auto s : e.getErrors())
							cout << s << endl;
					}
					break;
				}
				case 2:
				{
					cout << endl << "Provide the following in order to remove an event:" << endl;
					cout << endl << "Title: ";
					flushStdin();
					getline(cin, title);
					cout << "Number of people: ";
					cin >> nr_people;
					flushStdin();
					try {
						this->serv.removeEventService(title, nr_people);
						cout << "Event removed successfully!" << endl;
					}
					catch (RepositoryException& e) {
						cout << e.what() << endl;
					}
					break;
				}
				case 3:
				{
					cout << "Provide the following in order to update an event:" << endl;
					string newtitle = "", newdesc = "", newlink = "";
					int new_nr_people = -1;
					tm new_date_time = { 0 };

					cout << endl << "Title:";
					flushStdin();
					getline(cin, title);
					cout << "Number of people: ";
					cin >> nr_people;
					cout << "Provide new title, description, date, time, number of people and link: ";
					readEvent(newtitle, newdesc, new_date_time, new_nr_people, newlink);
					try {
						this->serv.updateEvent(newtitle, newdesc, new_date_time, new_nr_people, newlink, title, nr_people);
						cout << "Event updated successfully!" << endl;
					}
					catch (RepositoryException& e) {
						cout << e.what() << endl;
					}
					catch (EventException& e) {
						for (auto s : e.getErrors())
							cout << s << endl;
					}
					break;
				}
				case 4:
				{
					for(auto e: this->serv.getEvents())
						this->dispalyEvent(e);
					if(this->serv.nrEvents() == 0)
						cout << "No events to show!" << endl;
					break;
				}
				case 5:
				{
					break;
				}
				default:
				{
					cout << "Invalid command!" << endl;
					break;
				}
				}
			} while (option != 5);
			break;
		}
		case 2:
		{
			do {
				option = -1;
				userMenu();
				cin >> option;
				if (cin.fail())
				{
					flushStdin();
					option = -1;
				}
				switch (option)
				{
				case 1:
				{
					int montval;
					string month = "";
					cout << "Enter the month you want to see the events for (empty means all): ";
					flushStdin();
					getline(cin, month);
					if (month.length() == 0)
						montval = 0;
					else
					{
						try
						{
							montval = stoi(month);
						}
						catch (...)
						{
							cout << "try again!\n";
							break;
						}

					}
					vector<Event> events_orderd;
					this->serv.sortEvents_month(montval, events_orderd);
					if ((int)events_orderd.size() == 0)
					{
						cout << "No events to show!" << endl;
						break;
					}
					int index = 0, stop = -1, option = 2;
					do {
						if (option == 2)
						{
							this->dispalyEvent(events_orderd[index]);
							//open link
							string command = "start " + events_orderd[index].get_link();
							system(command.c_str());
						}
						seconduserMenu();
						cin >> option;
						if (cin.fail())
						{
							flushStdin();
							option = -1;
						}
						switch (option)
						{
						case 1:
						{
							string title = events_orderd[index].get_title();
							int nr = events_orderd[index].get_nr_people();
							try {
								this->serv.addEventToUserList(title, nr);
								cout << "Event added successfully!" << endl;
								nr++; 
								events_orderd[index].set_nr_people(nr);
							}
							catch (RepositoryException& e) {
								cout << e.what() << endl;
							}
							catch (FileException &e)
							{
								cout << e.what() << endl;
							}
							
							break;
						}
						case 2:
						{
							index++;
							if (index == (int)events_orderd.size())
								index = 0;
							break;
						}
						case 3:
						{
							stop = 1;
							break;
						}
						default:
						{
							cout << "Invalid command!" << endl;
							break;
						}
						}
					} while (stop == -1);
					break;

				}
				case 2:
				{
					string title;
					int nr;

					cout << "Enter the title and the number of people of the event you want to delete: " << endl;
					cout << "Title: ";
					flushStdin();
					getline(cin, title);
					cout << "Number of people: ";
					cin >> nr;
					flushStdin();
					try {
						this->serv.removeEventFromUserList(title, nr);
						cout<<"Event removed successfully!"<<endl;
					}
					catch (RepositoryException& e) { 
						cout << e.what() << endl; 
					}
					catch (FileException& e){
						cout << e.what() << endl; 
					}
					break;

				}
				case 3:
				{
					int len= (int)this->serv.getUserEvents().size();
					if (len == 0)
					{
						cout << "No events to show!" << endl;
					}
					else
						this->serv.displayUserEvents();
					break;
				}
				case 4:
				{
					break;
				}
				default:
				{
					cout << "Invalid command!" << endl;
					break;
				}
				}
			} while (option != 4);
			break;
		}
		case 0:
		{
			cout << "Goodbye!" << endl;
			break;
		}
		default:
		{
			cout << "Invalid command!" << endl;
			break;
		}
		}
	} while (option != 0);
}