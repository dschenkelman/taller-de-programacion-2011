#include <iostream>
#include <string>
using namespace std;
#include "User.h"

User::User(string name, int points)
{
	this->name = name;
	this->points = points;
}

User::~User(void)
{
}
