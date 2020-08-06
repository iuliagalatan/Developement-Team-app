#pragma once
#include <string>

enum UserType {
	programmer, tester
};

class User
{
public:
	User() {};
	User(std::string name, std::string type);

	std::string GetName() const;
	std::string GetType() const;

	void SetName(std::string name);
	void SetType(std::string type);

	UserType Type() const;

	friend std::istream& operator>>(std::istream& is, User& user);
private:
	std::string name;
	std::string type;
};

