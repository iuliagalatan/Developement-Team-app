#include <fstream>
#include <vector>
#include "DevelopmentTeam.h"
#include "User.h"
#include "ProgrammerObserver.h"
#include "TesterObserver.h"

#include "IssuesTableModel.h"

DevelopmentTeam::DevelopmentTeam(IssuesObservable& issuesObs): 
	issuesObs {issuesObs},
	fileTeam {"team.txt"}

{
	model = new IssuesTableModel{ this };
	sortModel = new QSortFilterProxyModel{ this };
	sortModel->setSourceModel(model);
	
	issuesObs.ReadIssues();
	GetTeam();
}

// Factory Method
Observer* DevelopmentTeam::CreateObserver(const User& user)
{
	Observer* observer = nullptr;
	switch (user.Type())
	{
	case UserType::programmer:
		observer = new ProgrammerObserver(issuesObs, QString::fromStdString(user.GetName()), sortModel);
		break;

	case UserType::tester:
		observer = new TesterObserver(issuesObs, QString::fromStdString(user.GetName()), sortModel);
		break;
	}

	return observer;
}

void DevelopmentTeam::StartWorking()
{
	for (const User& user : users)
	{
		Observer* observer = CreateObserver(user);
		issuesObs.addObserver(observer);
		observer->show();
	}
}

void DevelopmentTeam::GetTeam()
{
	std::ifstream fin(fileTeam);
	User user;
	while (fin >> user)
		users.push_back(user);
}

std::vector<Issue>& DevelopmentTeam::GetIssues()
{
	return issuesObs.GetIssues();
}

