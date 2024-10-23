#pragma once
#include <qwidget.h>
#include "Service.h"
#include"TableMode.h"
#include <qtableview.h>

class TableClass:public QWidget
{
private:
	Service& service;
	TableMode* tableMode;
	QTableView* tableView;
public:
	TableClass(Service& service);

};

