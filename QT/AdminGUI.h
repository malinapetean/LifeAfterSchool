#pragma once
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class AdminGUI:public QWidget
{
private:
	Service& service;
	QListWidget* eventslist;
	QLineEdit* title;
	QLineEdit* description;
	QLineEdit* dateandtime;
	QLineEdit* nrpeople;
	QLineEdit* link;
	QPushButton* addbutton;
	QPushButton* deletebutton;
	QPushButton* updatebutton;
	QPushButton* backbutton;
	QPushButton* undoButton;
	QPushButton* redoButton;

public:
	AdminGUI(Service& service);
private:
	void buildGUI();
	void populateList();
	void addButtonHandler();
	void deleteButtonHandler();
	void updateButtonHandler();
	void backbuttonHandler();
	void undoButtonHandler();
	void redoButtonHandler();
	void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;
};

