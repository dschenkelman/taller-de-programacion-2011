#include <iostream>
#include <string>
using namespace std;
#include "User.h"

User::User(std::string name, std::string password)
{
	this->name = name;
	this->password = password;
}

std::string User::getPassword()
{
	return this->password;
}

std::string User::getName()
{
	return this->name;
}

User::User(void)
{
}

User::~User(void)
{
}
