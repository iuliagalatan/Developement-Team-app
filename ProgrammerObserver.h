#pragma once

#include <QWidget>
#include "ui_ProgrammerObserver.h"
#include "Observer.h"
#include "IssuesObservable.h"
#include "IssuesTableModel.h"
#include <QSortFilterProxyModel>

class ProgrammerObserver : public QWidget, public Observer
{
	Q_OBJECT

public:
	ProgrammerObserver(IssuesObservable& issuesObs, const QString& name, QSortFilterProxyModel* model, QWidget* parent = Q_NULLPTR);
	~ProgrammerObserver();
	void BuildGui();

	void update() override;
	void show() override;

public slots:
	void OnBtnResolveClicked();
	void OnBtnRemoveClicked();
	void onTableClicked(const QModelIndex& index);
private:
	Ui::ProgrammerObserver ui;
	IssuesObservable& issuesObs;
	QString name;
	int row_to_delete = -1;
	Issue to_delete, to_update;
	QSortFilterProxyModel* model;
};
