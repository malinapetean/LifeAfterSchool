#include "TableMode.h"
#include <sstream>
#include<QFont>
#include<QBrush>

int TableMode::rowCount(const QModelIndex& parent) const
{
	int count = userEvents.size();
	return count;
}

int TableMode::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant TableMode::data(const QModelIndex& index, int role) const 
{
	int row = index.row();
	int col = index.column();
	if(role == Qt::DisplayRole || role == Qt::EditRole)
	{
		vector<Event> events = userEvents;
		Event e = events[row];
		switch (col)
		{
			case 0:
				return QString::fromStdString(e.get_title());
				break;
			case 1:
				return QString::fromStdString(e.get_description());
				break;
			case 2:
				{
				stringstream ss; 
				tm date = e.get_date_time();
				ss << put_time(&date, "%d/%m/%Y %H:%M");  
				return QString::fromStdString(ss.str()); 
			}
			break;
			case 3:
				return QString::fromStdString(to_string(e.get_nr_people()));
				break;
			case 4:
				return QString::fromStdString(e.get_link()); 
				break;
		default:
			break;
		}

	}
	if (role == Qt::BackgroundRole)
	{
		if (row % 2 == 0)
			return QColor{ Qt::lightGray };
	}
	if (role == Qt::FontRole)
	{
		
		QFont font("Times", 10, 10, true);
		return font;

	}
	return QVariant();
}

QVariant TableMode::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole)
	{
		if(orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return "Title";
				break;
			case 1:
				return "Description";
				break;
			case 2:
				return "Date";
				break;
			case 3:
				return "Number of people";
				break;
			case 4:
				return "Link";
				break;
			default:
				break;
			}
		}
	}
	if(role == Qt::FontRole)
	{
		QFont font("Times", 10, 10, true);
		font.setBold(true);
		return font;
	}
	return QVariant(); 
}

TableMode::~TableMode()
{
}
