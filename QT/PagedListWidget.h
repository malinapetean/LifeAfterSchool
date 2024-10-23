#pragma once

#include <QtWidgets/qlabel>
#include <QtWidgets/qpushbutton>
#include <QtWidgets/qlayout>
#include <QtWidgets/qlistwidget>
#include <QStringList>
#include <string>

using std::stoi;
using std::to_string;

class PagedListWidget : public QWidget
{
private:
	//boundaries
	int page_cap;
	int start;
	int end;

	//items + view
	QStringList items;
	QListWidget* list;

	//paging
	QPushButton* prev;
	QLabel* current;
	QPushButton* next;

	void initComponents();
	void initSignals();
	void displayNewPage();
	void loadListWidget();
public:
	PagedListWidget(QStringList& Items) noexcept;
	~PagedListWidget();
	QListWidgetItem* currentItem() const;
	QListWidgetItem* takeItem(int row);
	int row(const QListWidgetItem* item) const;
	QListWidget* getList() const noexcept { return list; }

	void Refresh(QStringList& New_Items) noexcept;
};

