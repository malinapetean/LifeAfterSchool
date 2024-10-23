#pragma once
#include"UserEventsList.h"
#include<QAbstractTableModel>

class TableMode:public QAbstractTableModel
{
private:
	vector<Event> userEvents;
	int nrEvents;
public:
	TableMode(vector<Event>elems, QObject* parent=NULL):userEvents{elems},QAbstractTableModel{parent}{
		this->nrEvents = userEvents.size();
	}
	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	~TableMode();
};

