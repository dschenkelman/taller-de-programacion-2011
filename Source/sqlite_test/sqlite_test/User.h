using namespace std;
#include <string>

#pragma once

class User
{
private:
	string name;
	int points;
public:
	User(string name, int points);
	~User(void);
};
