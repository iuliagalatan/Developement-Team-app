#pragma once

#include <QObject>
#include "Observable.h"
#include "Issue.h"

// Repository class for issues 
// and in the same time an observable class 
class IssuesObservable : public QObject, public Observable
{
	Q_OBJECT

public:
	IssuesObservable(QObject *parent = nullptr);
	~IssuesObservable();

	void AddIssue(std::string description, std::string reporter);
	void ReadIssues();
	std::vector<Issue>& GetIssues();

	int size() const;
public slots:
	void AddIssue(const Issue& issue);
	void RemoveIssue(const Issue& issue);
	void UpdateIssue(const Issue& issue);

private:
	std::vector<Issue> issues;
	std::string fileIssues;
};
