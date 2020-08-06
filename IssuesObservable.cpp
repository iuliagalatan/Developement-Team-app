#include "IssuesObservable.h"
#include <fstream>

IssuesObservable::IssuesObservable(QObject *parent)
	: QObject(parent), 
	fileIssues {"issues.txt"}
{
}

IssuesObservable::~IssuesObservable()
{
	// When the application is finished, the issues file will be updated
	// Save repository content to file
	std::ofstream fout(fileIssues);
	
	for (auto issue : issues)
		fout << issue << '\n';
}

void IssuesObservable::AddIssue(const Issue& issue)
{
	issues.push_back(issue);

	// notify all observer that an issue was added
	notify();
}

void IssuesObservable::ReadIssues()
{
	std::ifstream fin(fileIssues);
	Issue issue;
	while (fin >> issue)
		AddIssue(issue);
}

std::vector<Issue>& IssuesObservable::GetIssues()
{
	return issues;
}

int IssuesObservable::size() const
{
	return issues.size();
}

void IssuesObservable::RemoveIssue(const Issue& issue)
{
	for (auto it = issues.begin(); it != issues.end(); ++it)
		if (it->GetDescription() == issue.GetDescription())
		{
			issues.erase(it);
			// notify all observers that an issue was removed
			notify();
			break;
		}
}

void IssuesObservable::UpdateIssue(const Issue& issue)
{
	for (auto& iss : issues)
		if (iss.GetDescription() == issue.GetDescription())
		{
			iss = issue;
			// notify all observers that an issue was resolved
			notify();
			break;
		}
}
