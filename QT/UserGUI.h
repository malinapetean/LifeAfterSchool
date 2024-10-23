#pragma once
#include <qwidget.h>
#include "Service.h"
#include "PagedListWidget.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include"AbstractEventsList.h"

class UserGUI:public QWidget
{
private:
	Service& service;
	PagedListWidget* eventsList;
	QPushButton* filterButton;
	QPushButton* backButton;
	QPushButton* displayButton;
	QPushButton* addButton;
	QPushButton* displayEventsButton;
	QPushButton* deleteButton;
	QPushButton* tableButton;
	QLineEdit* monthLineEdit;


	int columnCount = 4;
	int rowCount = 0;


public:
	UserGUI(Service& service);
	void buildGUI();
	void populateList(vector<Event> list);
	void filterButtonHandler();
	void backButtonHandler();
	void displayButtonHandler();
	void displayEventsButtonHandler();
	void deleteButtonHandler();
	void addButtonHandler();
	void tableHandler();
};

