#include "PagedListWidget.h"

PagedListWidget::PagedListWidget(QStringList& Items) noexcept : items{ Items }, page_cap{ 1 }, start{ 0 }, end{ page_cap } {
	initComponents();
	initSignals();
}

void PagedListWidget::loadListWidget() {
	list->clear();
	for (int i = start, ct = 0; i < ((int)items.size() < end ? (int)items.size() : end) && ct != page_cap; i++, ct++) {
		list->addItem(items.at(i));

		//QListWidgetItem* item= list->item(i);
		//list->itemClicked(item);
		//if (item)
		//{
		//	this->list->takeItem(list->row(item)); 
		//	std::string link = item->text().split("\n")[4].toStdString(); 
		//	std::string command = "start " + link; 
		//	system(command.c_str()); //open the link in the default browser 
		//}
	}
	if (!(int)items.size())
		list->addItem("\t\t\t  Empty");
}

QListWidgetItem* PagedListWidget::currentItem() const
{
	return list->currentItem();
	
}

QListWidgetItem* PagedListWidget::takeItem(int row)
{
	return list->takeItem(row);
}

int PagedListWidget::row(const QListWidgetItem* item) const
{
	return list->row(item);
}

void PagedListWidget::Refresh(QStringList& New_Items) noexcept {
	items = New_Items;
	start = 0, end = New_Items.size() < page_cap ? New_Items.size() : page_cap;
	current->setText("1");
	prev->setEnabled(false);
	if ((int)items.size() > page_cap)
		next->setEnabled(true);
	else
		next->setEnabled(false);
	loadListWidget();
}

void PagedListWidget::initComponents() {
	QString button_style{ "background-color: lightblue; color: black; font-weight: bold; font-family: Consolas; border-radius: 2px" };
	//list-related
	auto ly = new QHBoxLayout();
	setLayout(ly);
	ly->insertStretch(0);

	auto main_layout = new QVBoxLayout();
	main_layout->insertStretch(0);
	list = new QListWidget();
	list->setMinimumSize(550, page_cap * 6 * 20);
	list->setMaximumSize(550, this->height());
	list->setStyleSheet("background-color: lightblue; color: black; font-family: Consolas; border-radius: 2px");
	QListWidgetItem* item = this->list->currentItem();
	loadListWidget();
	main_layout->addWidget(list);

	//navigation bar
	auto navigation_bar = new QHBoxLayout();
	navigation_bar->insertStretch(0, 10);
	prev = new QPushButton{ "<" };
	prev->setEnabled(false);
	prev->setFixedWidth(20);
	prev->setStyleSheet(button_style);
	/*prev->setStyleSheet("background-image: C:\\Users\\Cristi\\Desktop\\FACULTATE\\ANU 1\\sem2\\oop\\Lab10 - 11\\prev_page.png;"
			"background-repeat: no-repeat; background-position: center");*/
	current = new QLabel{ "1" };
	current->setAlignment(Qt::AlignCenter);
	current->setStyleSheet("color: black;");
	next = new QPushButton{ ">" };
	if ((int)items.size() < page_cap) next->setEnabled(false);
	next->setFixedWidth(20);
	next->setStyleSheet(button_style);
	navigation_bar->addWidget(prev);
	navigation_bar->addWidget(current);
	navigation_bar->addWidget(next);
	navigation_bar->insertStretch(4, 10);

	main_layout->addLayout(navigation_bar);
	main_layout->insertStretch(-1);
	ly->addLayout(main_layout);
	ly->insertStretch(-1);
}

void PagedListWidget::initSignals() {
	//prev clicked
	QObject::connect(prev, &QPushButton::clicked, [&]() {
		if (next->isEnabled() == false)
			next->setEnabled(true);
		start -= page_cap;
		end -= page_cap;
		int page_number = stoi(current->text().toStdString());
		page_number--;
		current->setText(QString::fromStdString(to_string(page_number)));
		loadListWidget();
		if (start <= 0)
			prev->setEnabled(false);
		});
	//next clicked
	QObject::connect(next, &QPushButton::clicked, [&]() {
		if (prev->isEnabled() == false)
			prev->setEnabled(true);
		start += page_cap;
		end += page_cap;
		int page_number = stoi(current->text().toStdString());
		page_number++;
		current->setText(QString::fromStdString(to_string(page_number)));
		loadListWidget();
		if (end >= (int)items.size())
			next->setEnabled(false);
		});
}

void PagedListWidget::displayNewPage() {

}

PagedListWidget::~PagedListWidget() {

}
