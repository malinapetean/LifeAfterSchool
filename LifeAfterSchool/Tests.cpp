//#include "Tests.h"
//
//Test::Test() 
//{
//}
//
//Test::~Test()
//{
//}
//
//void Test::testaddEvent()
//{
//
//    /*tm dateAndTime;
//    service.set_date_time(dateAndTime, 2020, 12, 1, 20, 0);
//    string title = "test", description = "test", link = "www.test";
//    int numberOfPeople = 1;
//    Event test = Event(title, description, dateAndTime, numberOfPeople, link);
//    try {
//        this->service.addEventService(title, description, dateAndTime, numberOfPeople, link);
//        assert(true);
//    }
//    catch (...)
//    {
//        if (this->service.searchEvent(title, numberOfPeople) == -1)
//            assert(false);
//        else
//            assert(true);
//    }
//    assert(test == service.getEvent(3));
//    try {
//        service.addEventService(title, description, dateAndTime, numberOfPeople, link);
//        assert(false);
//    }
//    catch (...)
//    {
//        assert(true);
//    }
//    assert(this->service.getEvent(3).get_title() == title);
//    assert(this->service.getEvent(3).get_description() == description);
//    assert(this->service.getEvent(3).get_link() == link);
//    assert(this->service.getEvent(3).get_nr_people() == numberOfPeople);
//    assert(this->service.getEvent(3).get_date_time().tm_mday == dateAndTime.tm_mday);
//    title = "";
//
//    try
//    {
//        this->service.addEventService(title, description, dateAndTime, numberOfPeople, link);
//        assert(false);
//    }
//    catch (...)
//    {
//        assert(true);
//    }
//    title = "test";
//    description = "";
//
//    try
//    {
//        this->service.addEventService(title, description, dateAndTime, numberOfPeople, link);
//        assert(false);
//    }
//    catch (...)
//    {
//        assert(true);
//    }
//
//    description = "test";
//    link = "";
//
//    try
//    {
//        this->service.addEventService(title, description, dateAndTime, numberOfPeople, link);
//        assert(false);
//    }
//    catch (...)
//    {
//        assert(true);
//    }
//
//    link = "test";
//    numberOfPeople = -1;
//
//    try
//    {
//        this->service.addEventService(title, description, dateAndTime, numberOfPeople, link);
//        assert(false);
//    }
//    catch (...)
//    {
//        assert(true);
//    }
//    numberOfPeople = 1;
//    dateAndTime.tm_year = -5000;
//
//    try
//    {
//        this->service.addEventService(title, description, dateAndTime, numberOfPeople, link);
//        assert(false);
//    }
//    catch (...)
//    {
//        assert(true);
//    }
//    dateAndTime.tm_year = 2023 - 1900;
//
//    std::cout << "Test add event passed!" << std::endl;*/
//}
//
//void Test::testremoveEvent()
//{
//
//    /*string title = "test";
//    int numberOfPeople = 1;
//    string title2 = "";
//
//    try {
//        service.removeEventService(title, numberOfPeople);
//        assert(true);
//    }
//    catch (...)
//    {
//        assert(false);
//    }
//    title = "test2";
//    numberOfPeople = 2;
//    try {
//        service.removeEventService(title, numberOfPeople);
//        assert(false);
//    }
//    catch (...)
//    {
//        assert(true);
//    }
//
//    cout << "Test remove event passed!" << endl;*/
//}
//
//void Test::testupdateEvent()
//{
//    /*string title = "test2";
//    int numberOfPeople = 1000;
//
//    string newTitle = "test", newDescription = "test2", newLink = "test2";
//    int newNumberOfPeople = 1;
//    tm newDateAndTime = std::tm();
//
//    try
//    {
//        this->service.updateEvent(newTitle, newDescription, newDateAndTime, newNumberOfPeople, newLink, title, numberOfPeople);
//        assert(false);
//    }
//    catch (...)
//    {
//        assert(true);
//    }
//
//    title = "test";
//    numberOfPeople = 1;
//
//    try
//    {
//        this->service.updateEvent(newTitle, newDescription, newDateAndTime, newNumberOfPeople, newLink, title, numberOfPeople);
//        assert(false);
//    }
//    catch (...)
//    {
//        assert(true);
//    }
//
//    this->service.set_date_time(newDateAndTime, 2023, 1, 1, 20, 0);
//
//    try
//    {
//        this->service.updateEvent(newTitle, newDescription, newDateAndTime, newNumberOfPeople, newLink, title, numberOfPeople);
//        assert(false);
//    }
//    catch (...)
//    {
//        assert(true);
//    }
//
//    newTitle = "test2";
//    newNumberOfPeople = 2;
//
//    try
//    {
//        this->service.updateEvent(newTitle, newDescription, newDateAndTime, newNumberOfPeople, newLink, title, numberOfPeople);
//        assert(false);
//    }
//    catch (...)
//    {
//        assert(true);
//    }
//
//    std::cout << "Test update event passed!" << std::endl;*/
//}
//
//void Test::testgetallEvents()
//{
//    //assert(service.getEvents().size() == service.nrEvents());
//}
//
//void Test::testall()
//{/*
//    this->testaddEvent();
//    this->testremoveEvent();
//    this->testoperator();
//    this->testupdateEvent();
//    this->testgetallEvents();
//    this->testuserrepo();
//    this->testUserEventsService();*/
//    cout << "All tests passed" << endl;
//}
//
//void Test::testoperator()
//{
//    /*ostringstream output;
//    string t = "title";
//    string d = "desc";
//    tm date = { 2023,4,11,20,00 };
//    int nr = 20;
//    string l = "link";
//
//    Event e = Event();
//    e.set_title(t);
//    e.set_description(d);
//    e.set_date_time(date);
//    e.set_nr_people(nr);
//    e.set_link(l);
//    e.get_link();
//    e.get_date_time();
//    e.get_description();
//
//    output << e;*/
//
//}
//
//void Test::testuserrepo()
//{
//
//
//
//
//}
//
//void Test::testUserEventsService()
//{
//
//    //string t = "Law party";
//    //int nr = 150;
//    ////add
//    //try {
//    //    service.addEventToUserList(t, nr);
//    //    assert(true);
//    //}
//    //catch (...)
//    //{
//    //    assert(false);
//    //}
//    //nr = 151;
//    //try {
//    //    service.addEventToUserList(t, nr);
//    //    assert(false);
//    //}
//    //catch (...)
//    //{
//    //    assert(true);
//    //}
//    ////get
//    //assert(service.getUserEvent(0).get_title() == "Law party");
//
//    ////remove
//    //try {
//    //    service.removeEventFromUserList(t, nr);
//    //    assert(true);
//    //}
//    //catch (...)
//    //{
//    //    assert(false);
//    //}
//    //nr = 150;
//    //try {
//    //    service.removeEventFromUserList(t, nr);
//    //    assert(false);
//    //}
//    //catch (...)
//    //{
//    //    assert(true);
//    //}
//
//
//    ////compare dates
//    //tm date;
//    //date.tm_year = 2024;
//    //date.tm_mon = 3;
//    //date.tm_mday = 10;
//    //date.tm_hour = 10;
//    //date.tm_min = 00;
//    //tm date2;
//    //date2.tm_year = 2023;
//    //date2.tm_mon = 3;
//    //date2.tm_mday = 10;
//    //date2.tm_hour = 10;
//    //date2.tm_min = 00;
//    //assert(service.compareDates(date, date2) == true);
//    //date.tm_mon = 4;
//    //date.tm_year = 2023;
//    //assert(service.compareDates(date, date2) == true);
//    //date.tm_mon = 3;
//    //date.tm_mday = 11;
//    //assert(service.compareDates(date, date2) == true);
//    //date.tm_mday = 10;
//    //date.tm_hour = 11;
//    //assert(service.compareDates(date, date2) == true);
//    //date.tm_hour = 10;
//    //date.tm_min = 1;
//    //assert(service.compareDates(date, date2) == true);
//    //date.tm_min = 0;
//    //assert(service.compareDates(date, date2) == false);
//
//    ////sort events by month
//
//    //vector<Event> events;
//    //service.sortEvents_month(4, events);
//    //vector<Event> events2;
//    //service.sortEvents_month(0, events2);
//
//    cout << "Test user events passed!" << endl;
//
//
//}