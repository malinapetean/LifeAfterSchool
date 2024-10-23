#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QT.h"
#include<QtCore>
#include<QtGui>
#include<QtCharts/qchart.h>


class QT : public QMainWindow
{
    Q_OBJECT

public:
    QT(QWidget *parent = nullptr);
    ~QT();

private:
    Ui::QTClass ui;
};
