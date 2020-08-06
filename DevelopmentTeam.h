#pragma once

#include <QtWidgets/QWidget>
#include "ui_DevelopmentTeam.h"
#include "IssuesTableModel.h"
#include <QSortFilterProxyModel>
#include "IssuesObservable.h"
#include "Observer.h"
#include "User.h"


class DevelopmentTeam 
{
	Q_OBJECT

public:
	DevelopmentTeam(IssuesObservable& issues);

	void StartWorking();
	void GetTeam();
	std::vector<Issue>& GetIssues();

	// Factory Method (create a new observer)
	Observer* CreateObserver(const User& user);

private:
	//Ui::DevelopmentTeamClass ui;
	std::vector<User> users;
	IssuesObservable& issuesObs;
	std::string fileTeam;
	IssuesTableModel* model;
	QSortFilterProxyModel* sortModel;
};
