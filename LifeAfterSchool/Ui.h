#pragma once
#include"Service.h"

class Ui
{
private:
	Service serv;
public:
	Ui(Service s);
	void menu();
	void adminMenu();
	void start();
	void readEvent(string& title, string& desc, tm& date_time, int& nrPers, string& link);
	void flushStdin();
	void userMenu();
	void seconduserMenu();
	void dispalyEvent(Event& e);
};