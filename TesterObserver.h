#pragma once

#include <QWidget>
#include "ui_TesterObserver.h"
#include "IssuesObservable.h"
#include "IssuesTableModel.h"
#include <QSortFilterProxyModel>


class TesterObserver : public QWidget, public Observer
{
	Q_OBJECT

public:
	TesterObserver(IssuesObservable& issuesObs, const QString& name, QSortFilterProxyModel* model,  QWidget* parent = Q_NULLPTR);
	~TesterObserver();

	void update() override;
	void show() override;

public slots:
	void OnBtnAddClicked();
	void OnBtnRemoveClicked();
	void onTableClicked(const QModelIndex& index);

private:
	Ui::TesterObserver ui;
	IssuesObservable& issuesObs;
	QString name;
	int row_to_delete = -1;
	Issue to_delete;
	QSortFilterProxyModel* model;
};
