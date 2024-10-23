#include "AdminGUI.h"
#include <qlayout.h>
#include <qlabel.h>
#include <QKeyEvent>
#include"GUI.h"
#include <qmessagebox.h>


AdminGUI::AdminGUI(Service& service) : service{ service }
{
	this->buildGUI();
	this->populateList();
	
	QObject::connect(this->addbutton, &QPushButton::clicked, this, &AdminGUI::addButtonHandler);
	QObject::connect(this->deletebutton, &QPushButton::clicked, this, &AdminGUI::deleteButtonHandler);
	QObject::connect(this->updatebutton, &QPushButton::clicked, this, &AdminGUI::updateButtonHandler);
	QObject::connect(this->backbutton, &QPushButton::clicked, this, &AdminGUI::backbuttonHandler);
	/*QObject::connect(this->eventslist, &QListWidget::itemSelectionChanged, [this]() {
		QListWidgetItem* item = this->eventslist->currentItem();
		if (item)
		{

			string link = item->text().split("\n")[4].toStdString();
			string command = "start " + link;
			system(command.c_str());

		}
		});*/
	QObject::connect(this->undoButton, &QPushButton::clicked, this, &AdminGUI::undoButtonHandler);
	QObject::connect(this->redoButton, &QPushButton::clicked, this, &AdminGUI::redoButtonHandler); 
}

void AdminGUI::buildGUI()
{
	QHBoxLayout* mainLayout = new QHBoxLayout{ this };
	QPalette pal1 = this->palette();
	pal1.setColor(QPalette::Window, QColor(204, 232, 224));
	this->setPalette(pal1);
	
	this->eventslist = new QListWidget{};
	mainLayout->addWidget(this->eventslist);
	///set blue color for the list
	QPalette pal = this->eventslist->palette();
	pal.setColor(QPalette::Base, QColor(166, 232, 225));
	this->eventslist->setPalette(pal);
	//set the font for title

	QGridLayout* rightLayout = new QGridLayout{};
	mainLayout->addLayout(rightLayout);

	QLabel* titleLabel = new QLabel{ "Title" };
	titleLabel->setStyleSheet("QLabel { background-color : lightblue; color : black; }");
	this->title= new QLineEdit{};

	QLabel* descriptionLabel = new QLabel{ "Description" };
	descriptionLabel->setStyleSheet("QLabel { background-color : lightblue; color: black; }");
	this->description = new QLineEdit{};

	QLabel* dateTimeLabel = new QLabel{ "Date and Time" };
	dateTimeLabel->setStyleSheet("QLabel { background-color : lightblue; color : black; }");
	this->dateandtime = new QLineEdit{};

	QLabel* nrparticipantsLabel = new QLabel{ " Number Participants" };
	nrparticipantsLabel->setStyleSheet("QLabel { background-color : lightblue; color : black; }");
	this->nrpeople= new QLineEdit{};

	QLabel* linkLabel = new QLabel{ "Link" };
	linkLabel->setStyleSheet("QLabel { background-color : lightblue; color : black; }");
	this->link = new QLineEdit{};

	rightLayout->addWidget(titleLabel, 0, 0);
	rightLayout->addWidget(this->title, 0, 1);
	rightLayout->addWidget(descriptionLabel, 1, 0);
	rightLayout->addWidget(this->description, 1, 1);
	rightLayout->addWidget(dateTimeLabel, 2, 0);
	rightLayout->addWidget(this->dateandtime, 2, 1);
	rightLayout->addWidget(nrparticipantsLabel, 3, 0);
	rightLayout->addWidget(this->nrpeople, 3, 1);
	rightLayout->addWidget(linkLabel, 4, 0);
	rightLayout->addWidget(this->link, 4, 1);

	this->addbutton= new QPushButton{ "Add" };
	addbutton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	addbutton->setFont(QFont("Arial",10,5000,true));
	rightLayout->addWidget(this->addbutton, 5, 0);

	this->deletebutton = new QPushButton{ "Delete" };
	deletebutton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	deletebutton->setFont(QFont("Arial", 10, 5000, true));
	rightLayout->addWidget(this->deletebutton, 5, 1);

	this->updatebutton= new QPushButton{ "Update" };
	updatebutton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	updatebutton->setFont(QFont("Arial", 10, 5000, true));
	rightLayout->addWidget(this->updatebutton, 6, 1);

	this->backbutton = new QPushButton{ "Back" };
	backbutton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	backbutton->setFont(QFont("Arial", 10, 5000, true));
	rightLayout->addWidget(this->backbutton, 6, 0);

	this->undoButton = new QPushButton{ "Undo" };
	undoButton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	undoButton->setFont(QFont("Arial", 10, 5000, true));
	rightLayout->addWidget(this->undoButton, 7, 0);

	this->redoButton = new QPushButton{ "Redo" };
	redoButton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	redoButton->setFont(QFont("Arial", 10, 5000, true));
	rightLayout->addWidget(this->redoButton, 7, 1);
}

void AdminGUI::populateList()
{
	this->eventslist->clear();
	
	for (auto event : this->service.getEvents())
	{
		QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(event.tostring()));
		this->eventslist->addItem(item);
	}
}

void AdminGUI::addButtonHandler()
{
	string title = this->title->text().toStdString();
	string description = this->description->text().toStdString();
	QString dateandtime = this->dateandtime->text();
	tm dateTime= this->service.convertStringToTime(dateandtime.toStdString());
	int nrpeople = this->nrpeople->text().toInt();
	string link = this->link->text().toStdString();
	try {
		this->service.addEventService(title, description, dateTime, nrpeople, link);
		this->populateList();
	}
	catch (exception& e)
	{
		QMessageBox::critical(this, "Error", e.what());
	}
	
}

void AdminGUI::deleteButtonHandler()
{
	QListWidgetItem* item = this->eventslist->currentItem();
	if (item)
	{
		this->eventslist->takeItem(eventslist->row(item));
		string title = item->text().split("\n")[0].toStdString();
		int nrpeople = item->text().split("\n")[3].toInt();
		this->service.removeEventService(title,nrpeople);
	}
}

void AdminGUI::updateButtonHandler()
{
	string newtitle = this->title->text().toStdString();
	string newdescription = this->description->text().toStdString();
	QString newdateandtime = this->dateandtime->text();
	tm dateTime = this->service.convertStringToTime(newdateandtime.toStdString());
	int newnrpeople = this->nrpeople->text().toInt();
	string newlink = this->link->text().toStdString();
	QListWidgetItem* item = this->eventslist->currentItem();
	if (item)
	{
		string title = item->text().split("\n")[0].toStdString();
		int nrpeople = item->text().split("\n")[3].toInt();
		try {
			this->service.updateEvent(newtitle, newdescription, dateTime, newnrpeople, newlink, title, nrpeople);
			this->populateList();
		}
		catch (exception& e)
		{
			QMessageBox::critical(this, "Error", e.what());
		}
		
	}
}

void AdminGUI::backbuttonHandler()
{
	this->hide();
	GUI* gui = new GUI{ this->service };
	gui->show();
}

void AdminGUI::undoButtonHandler()
{
	try {
		this->service.undo();
		this->populateList();
	}
	catch (exception& e)
	{
		QMessageBox::critical(this, "Error", "No more undos");
	}
}

void AdminGUI::redoButtonHandler()
{
	try {
		this->service.redo();
		this->populateList();
	}
	catch (exception& e)
	{
		QMessageBox::critical(this, "Error", "No more redos");
	}
}

void AdminGUI::keyPressEvent(QKeyEvent* event)
{
	QWidget::keyPressEvent(event);
	
	int k = event->key();
	Qt::KeyboardModifiers modifiers = event->modifiers(); 

	if (k == Qt::Key_Z && (modifiers & Qt::ControlModifier)) 
		this->undoButtonHandler(); 
	if (k == Qt::Key_Y && (modifiers & Qt::ControlModifier)) 
		this->redoButtonHandler(); 

}




