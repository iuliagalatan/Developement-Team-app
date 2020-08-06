#include "DevelopmentTeam.h"
#include <QtWidgets/QApplication>
#include "IssuesObservable.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	IssuesObservable issuesObs;
	DevelopmentTeam team { issuesObs };
	team.StartWorking();

	return a.exec();
}
