#pragma once
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include "Event.h"

#define QT_CHARTS_USE_NAMESPACE

class ChartWidget : public QWidget {
    Q_OBJECT

public:
    ChartWidget(const std::vector<Event>& events, QWidget* parent = nullptr);

private:
    void createBarChart(const std::vector<Event>& events);
};
