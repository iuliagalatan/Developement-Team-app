#include "Issue.h"
#include <vector>
#include "Util.h"

Issue::Issue(const std::string& description, Status status, const std::string reporter, const std::string solver):
	description {description},
	status {status},
	reporter {reporter},
	solver {solver}
{
}

std::string Issue::GetDescription() const
{
	return description;
}

std::string Issue::GetStatus() const
{
	if (status == open)
		return "open";
	return "closed";
}

std::string Issue::GetReporter() const
{
	return reporter;
}

std::string Issue::GetSolver() const
{
	return solver;
}

std::ostream& operator<<(std::ostream& os, const Issue& issue)
{
	std::string status;
	std::string solver = "nobody";
	if (issue.status == Issue::closed)
	{
		status = "closed";
		solver = issue.solver;
	}
	else
		status = "open";

	return os << issue.description << ',' << status << ','
			  << issue.reporter << ',' << solver;
}

std::istream& operator>>(std::istream& is, Issue& issue)
{
	std::string line;
	getline(is, line);
	if (line == "")   return is;

	std::vector<std::string> tokens = split(line, ',');
	if (tokens.size() != 4) return is;

	issue.description = trim(tokens[0]);
	
	std::string status = trim(tokens[1]);
	if (status == "closed")
		issue.status = Issue::closed;
	else
		issue.status = Issue::open;

	issue.reporter = trim(tokens[2]);

	issue.solver = trim(tokens[3]);
	
	return is;
}
