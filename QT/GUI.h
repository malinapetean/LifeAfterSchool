#pragma once
#include <qwidget.h>
#include "Service.h"
#include "fileUserEventsList.h"
#include "CSVFileUserEvents.h"
#include "HTMLFileUserEvents.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <QComboBox>
class GUI : public QWidget
{
private:
	string type = "empty";
	Service& service;
	QPushButton* adminButton;
	QPushButton* userButton;
	QPushButton* saveButton;
	QPushButton* chartButton;
	FileUserEventsList* filetype;
	QComboBox* fileType;


public:
	GUI(Service& service);
	void bGUI();
	void adminButtonHandler();
	void userButtonHandler();
	void saveButtonHandler();
	void createChart();
	FileUserEventsList* getFileType() { return this->filetype; }

};

