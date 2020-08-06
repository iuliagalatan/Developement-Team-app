#pragma once
#include <qabstractitemmodel.h>

class DevelopmentTeam;

class IssuesTableModel :  public QAbstractTableModel
{
public:
	IssuesTableModel(DevelopmentTeam* service) : 
		QAbstractTableModel(),
		service { service }
	{
	}
	IssuesTableModel(const IssuesTableModel&) = delete;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	bool insertRows(int row, int count, const QModelIndex& parent) override;
	bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
	Qt::ItemFlags flags(const QModelIndex& index) const;

private:
	DevelopmentTeam* service;
};

