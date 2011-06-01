#include "User.h"
#include "List.h"
#pragma once

class Game
{
private:
	User userOne;
	User userTwo;
	int points;
public:
	Game(User u1, User u2, int pts);
	User getUserOne();
	User getUserTwo();
	List<User> getUsers();
	int getPoints();
	~Game(void);
};
