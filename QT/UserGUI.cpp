#include "UserGUI.h"
#include "GUI.h"
#include"TableClass.h"
#include <qlayout.h>
#include <qlabel.h>
#include <qmessagebox.h>

UserGUI::UserGUI(Service& service) : service{ service }
{
	this->buildGUI();
	QObject::connect(this->filterButton, &QPushButton::clicked, this, &UserGUI::filterButtonHandler);
	QObject::connect(this->backButton, &QPushButton::clicked, this, &UserGUI::backButtonHandler);
	QObject::connect(this->displayEventsButton, &QPushButton::clicked, this, &UserGUI::displayEventsButtonHandler);
	QObject::connect(this->addButton, &QPushButton::clicked, this, &UserGUI::addButtonHandler);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &UserGUI::deleteButtonHandler);
	QObject::connect(this->displayButton, &QPushButton::clicked, this, &UserGUI::displayButtonHandler);
	QObject::connect(this->eventsList->getList(), &QListWidget::itemSelectionChanged, [this]() {
		QListWidgetItem* item = this->eventsList->currentItem();
		if (item)
		{
			string link = item->text().split("\n")[4].toStdString();
			string command = "start " + link;
			system(command.c_str());
		}
		}
	);
	QObject::connect(this->tableButton, &QPushButton::clicked, this, &UserGUI::tableHandler);


}

void UserGUI::buildGUI()
{
	QHBoxLayout* mainLayout = new QHBoxLayout{ this };
	QPalette pal1 = this->palette();
	pal1.setColor(QPalette::Window, QColor(204, 232, 224));
	this->setPalette(pal1);

	QStringList* list = new QStringList{};
	
	eventsList = new PagedListWidget(*list);
	mainLayout->addWidget(eventsList);


	QVBoxLayout* rightLayout = new QVBoxLayout{};
	mainLayout->addLayout(rightLayout);

	QLabel* eventslisttext = new QLabel{ "Events list by month (empty=all)" };
	eventslisttext->setStyleSheet("QLabel { background-color : lightblue; color : black; }");
	eventslisttext->setAlignment(Qt::AlignAbsolute);
	eventslisttext->setMaximumSize(this->width(), 20);
	rightLayout->addWidget(eventslisttext);
	
	

	QGridLayout* rightLayout2 = new QGridLayout{};

	QLabel* monthLabel = new QLabel{ "Month" };
	monthLabel->setStyleSheet("QLabel { background-color : lightblue; color : black; }");
	monthLabel->setMidLineWidth(50);
	rightLayout2->addWidget(monthLabel, 0, 0);
	this->monthLineEdit = new QLineEdit{};
	rightLayout2->addWidget(this->monthLineEdit, 0, 1);

	this->filterButton = new QPushButton{ "Show" };
	this->filterButton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	rightLayout2->addWidget(this->filterButton, 1, 0);

	this->backButton = new QPushButton{ "Back" };
	this->backButton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	rightLayout2->addWidget(this->backButton, 4, 1);

	this->addButton = new QPushButton{ "Add" };
	this->addButton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	this->addButton->setFont(QFont("Arial", 10, 5000, true));
	rightLayout2->addWidget(this->addButton, 2, 0);

	this->deleteButton = new QPushButton{ "Delete" };
	this->deleteButton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	rightLayout2->addWidget(this->deleteButton, 2, 1);

	this->displayEventsButton = new QPushButton{ "Display User Events" };
	this->displayEventsButton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	rightLayout2->addWidget(this->displayEventsButton, 3, 0);



	this->displayButton = new QPushButton{ "Display Saved File" };
	this->displayButton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	rightLayout2->addWidget(this->displayButton, 4, 0);

	this->tableButton = new QPushButton{ "Table View" };
	this->tableButton->setStyleSheet("QPushButton { background-color : lightblue; color : black; }");
	rightLayout2->addWidget(this->tableButton, 5, 0);

	rightLayout->addLayout(rightLayout2);




}

void UserGUI::populateList(vector<Event> events)
{
	QStringList* list = new QStringList{};
	for (auto& e : events)
	{
		QString itemInList = QString::fromStdString(e.tostring());
		list->append(itemInList);
	}
	eventsList->Refresh(*list);
}

void UserGUI::filterButtonHandler()
{	
	vector<Event> eventsorderd;
	QString month = this->monthLineEdit->text();
	if(month.toStdString().size()==0)
	{
		month ="0";
	}
	this->service.sortEvents_month(stoi(month.toStdString()), eventsorderd);
	this->populateList(eventsorderd);

}

void UserGUI::backButtonHandler()
{
	this->close();
	GUI *gui = new GUI{ this->service };
	gui->show();
}

void UserGUI::displayButtonHandler()
{
	this->service.displayUserEvents();
}

void UserGUI::displayEventsButtonHandler()
{
	this->populateList(service.getUserEvents());
}

void UserGUI::deleteButtonHandler()
{
	QListWidgetItem* item = this->eventsList->currentItem();
	if (item)
	{
		this->eventsList->takeItem(eventsList->row(item));
		string title = item->text().split("\n")[0].toStdString();
		int nrpeople = item->text().split("\n")[3].toInt();
		try
		{
			this->service.removeEventFromUserList(title, nrpeople);
			populateList(service.getUserEvents());
		}
		catch (exception& e)
		{
			QMessageBox::critical(this, "Error", e.what());
		}
	}
}

void UserGUI::addButtonHandler()
{
	QListWidgetItem* item = this->eventsList->currentItem();
	if (item)
	{
		this->eventsList->takeItem(eventsList->row(item));
		string title = item->text().split("\n")[0].toStdString();
		int nrpeople = item->text().split("\n")[3].toInt();
		try
		{
			this->service.addEventToUserList(title,nrpeople);
		}
		catch (exception& e)
		{
			QMessageBox::critical(this, "Error", e.what());
		}
	}
	
}

void UserGUI::tableHandler()
{
	
	TableClass* table = new TableClass(service);
	table->show();

}
