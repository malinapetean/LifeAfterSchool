#include "QT.h"
#include <QtCharts/qlineseries.h>
#include <QtCharts/qchartview.h>

QT::QT(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QLineSeries *series = new QLineSeries();
	series->append(1, 0);
	series->append(2, 0);
	series->append(3, 0);
	series->append(4, 6);
	series->append(5, 1);
	series->append(6, 0);
	series->append(7, 0);
	series->append(8, 0);
	series->append(9, 0);
	series->append(10, 0);
	series->append(11, 0);
	series->append(12, 0);

	QChart *chart = new QChart();
	chart->legend()->hide();
	chart->addSeries(series);
	chart->createDefaultAxes();
	chart->axes(Qt::Vertical).first()->setRange(0, 6);
	chart->axes(Qt::Horizontal).first()->setRange(0, 12);
	chart->setVisible(true);

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->setVisible(true);

	setCentralWidget(chartView);
}

QT::~QT()
{}
