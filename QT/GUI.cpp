#include "GUI.h"
#include <qlayout.h>
#include <qlabel.h>
#include "AdminGUI.h"
#include "UserGUI.h"
#include <qmessagebox.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qchart.h>
#include <qmainwindow.h>
#include <chartwidget.h>


GUI::GUI(Service& service): service{ service }
{
	this->bGUI();
	QObject::connect(this->adminButton, &QPushButton::clicked, this, &GUI::adminButtonHandler);
	QObject::connect(this->userButton, &QPushButton::clicked, this, &GUI::userButtonHandler);
	QObject::connect(this->saveButton, &QPushButton::clicked, this, &GUI::saveButtonHandler);
	QObject::connect(this->chartButton, &QPushButton::clicked, this, &GUI::createChart);
}

void GUI::bGUI()
{
	QVBoxLayout* mainLayout = new QVBoxLayout{ this };
	QPalette pal1 = this->palette();
	pal1.setColor(QPalette::Window, QColor(204, 232, 224));
	this->setPalette(pal1);

	this->fileType = new QComboBox{};
	this->fileType->setStyleSheet("QComboBox { background-color : lightblue; color : black; }");
	this->fileType->addItem("empty");
	this->fileType->addItem("CSV");
	this->fileType->addItem("HTML");


	this->adminButton = new QPushButton{ "Admin" };
	this->adminButton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	this->userButton = new QPushButton{ "User" };
	this->userButton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	this->saveButton = new QPushButton{ "Save" };
	this->saveButton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	this->chartButton = new QPushButton{ "Chart" };
	this->chartButton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");

	mainLayout->addWidget(this->adminButton);
	mainLayout->addWidget(this->userButton);
	mainLayout->addWidget(this->fileType);
	mainLayout->addWidget(this->saveButton);
	mainLayout->addWidget(this->chartButton);
}



void GUI::adminButtonHandler()
{
	AdminGUI* admin = new AdminGUI{ this->service };
	admin->show();
	this->hide();
}

void GUI::userButtonHandler()
{
	if (type == "empty")
	{
		QMessageBox::critical(this, "Error", "Please select a file type!");
		return;
	}
	UserGUI* user = new UserGUI{ this->service };
	user->show();
	this->hide();
}

void GUI::saveButtonHandler()
{
	this->type = this->fileType->currentText().toStdString();
	if (this->type == "HTML")
	{
		this->filetype= new HTMLFileUserEventsList{ "events.html" };
		Repository repo{ "D://mycode//facultate//SEM II//OOP//Lab-homework//oop-a8-9-916-Petean-Anamaria//LifeAfterSchool//events.txt" };
		this->service= Service{ repo, this->filetype };
	}
	else if (this->type == "CSV")
	{
		this->filetype = new CSVFileUserEventsList{ "events.csv" };
	}
	
}

void GUI::createChart()
{
	std::vector<Event> events = this->service.getEvents();
	ChartWidget* chart = new ChartWidget{ events };
	chart->show();
	
	
	
}
