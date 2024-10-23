#include "TableClass.h"
#include <qlayout.h>

TableClass::TableClass(Service& service):service{service}
{
	QHBoxLayout* layout = new QHBoxLayout{ this };
	QPalette pal1 = this->palette();
	pal1.setColor(QPalette::Window, QColor(204, 232, 224));
	this->setPalette(pal1);

	tableView = new QTableView{};
	TableMode* model = new TableMode(service.getUserEvents());
	tableView->setModel(model);
	tableView->resizeRowsToContents();
	tableView->resizeColumnsToContents();

	layout->addWidget(tableView);
}
