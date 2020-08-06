#include "Util.h"
#include "User.h"

User::User(std::string name, std::string type) : name {name}, type {type}
{
}

std::string User::GetName() const
{
	return name;
}

std::string User::GetType() const
{
	return type;
}

void User::SetName(std::string name)
{
	this->name = name;
}

void User::SetType(std::string type)
{
	this->type = type;
}

UserType User::Type() const
{
	if (type == "programmer")
		return UserType::programmer;
	return UserType::tester;

}

std::istream& operator>>(std::istream& is, User& user)
{
	std::string line;
	getline(is, line);
	if (line == "")   return is;

	std::vector<std::string> tokens = split(line, ',');
	if (tokens.size() != 2) return is;

	user.name = trim(tokens[0]);
	user.type = trim(tokens[1]);

	return is;
}
