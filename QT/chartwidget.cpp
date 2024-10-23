#include "chartwidget.h"
#include <qlayout.h>

ChartWidget::ChartWidget(const std::vector<Event>& events, QWidget* parent) : QWidget{ parent }
{
	this->createBarChart(events);
}

void ChartWidget::createBarChart(const std::vector<Event>& events)
{
    QBarSet* barSet = new QBarSet("Events");
    std::map<int, int> monthCount; // key = month, value = number of events in that month
    for (Event event : events) {
           monthCount[event.get_date_time().tm_mon]++;
    }

    for (const auto& pair : monthCount) { 
        *barSet << pair.second; 
    }

    QBarSeries* series = new QBarSeries(); // create a new bar series
    series->append(barSet); // append the barSet to the series

    QChart* chart = new QChart(); // create a new chart
    chart->addSeries(series);
    chart->setTitle("Number of Events per Month");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories; // list of categories
    for (const auto& pair : monthCount) { // for each pair in sizeCount
        categories << QString::number(pair.first); // add the size to the categories
    }

    QBarCategoryAxis* axisX = new QBarCategoryAxis(); // create a new bar category axis
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Find the maximum value in the sizeCount map for the Y axis range to use it in the chart ( to set the maximum value of the Y axis to the maximum value in the sizeCount map)
    auto maxElement = std::max_element(monthCount.begin(), monthCount.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });
    int maxValue = (maxElement != monthCount.end()) ? maxElement->second : 0;

    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(0, maxValue);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}
