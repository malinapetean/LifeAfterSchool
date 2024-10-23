
#include"GUI.h"
#include<QtWidgets/QApplication>
#include"CSVFileUserEvents.h"
#include<QtCharts/QChart>
#include<QtCharts/QChartView>
#include<QtCharts/QBarSeries>
#include<QtCharts/QBarSet>
#include<QtCharts/QLegend>
#include<QtCharts/QBarCategoryAxis>
#include<QtCharts/QHorizontalStackedBarSeries>
#include<QtCharts/QCategoryAxis>
#include <QtCharts/qlineseries.h>


void run() {
	/*try {
		Repository repo("events.txt");
		FileUserEventsList* file = nullptr;
		cout << "Choose the type of file you want to save the user events in(CSV/HTML) : \n";
		string fileType{};
		cin >> fileType;
		while (fileType != "CSV" && fileType != "HTML")
		{
			cout << "Invalid file type! Please choose between CSV and HTML: ";
			cin >> fileType;
		}
		if (fileType == "CSV") 
			file = new CSVFileUserEventsList("events.csv"); 
		else
			file = new HTMLFileUserEventsList("events.html"); 
		Service service{ repo, file }; 
		Ui ui{ service }; 
		ui.start(); 
	}
	catch (FileException& ) {
		cout<<"Repository file could not be opened!\n";
	}*/
}

int main(int argc, char* argv[]) {
	
	QApplication a(argc, argv);

	Repository repo("D://mycode//facultate//SEM II//OOP//Lab-homework//oop-a8-9-916-Petean-Anamaria//LifeAfterSchool//events.txt");
	FileUserEventsList* file = nullptr;
	file = new CSVFileUserEventsList("events.csv");
	Service service{ repo, file };
	GUI gui{ service };
	gui.show();
	return a.exec();
	//run();
	return 0;
}

