#pragma once
#include <string>
#include <iostream>


class Issue
{
public:
	enum Status {
		open, closed
	};

	Issue() {}
	Issue(const std::string& description, Status status, const std::string reporter, const std::string solver);

	std::string GetDescription() const;
	std::string GetStatus() const;
	std::string GetReporter() const;
	std::string GetSolver() const;

	friend std::ostream& operator << (std::ostream& os, const Issue& issue);
	friend std::istream& operator >> (std::istream& is, Issue& issue);
private:
	std::string description;
	Status status;
	std::string reporter;
	std::string solver;
};

