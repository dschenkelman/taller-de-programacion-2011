#include <string>
#pragma once

using namespace std;

class User
{
private:
	std::string name;
	std::string password;
public:
	User(string name, std::string password);
	std::string getPassword();
	std::string getName();
	~User(void);
};
