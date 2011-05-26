#include "Game.h"

Game::Game(void)
{
}

Game::Game(User u1, User u2, int pts)
{
	this->userOne = u1;
	this->userTwo = u2;
	this->points = pts;
}

int Game::getPoints()
{
	return this->points;
}

User Game::getUserOne()
{
	return this->userOne;
}

User Game::getUserTwo()
{
	return this->userTwo;
}

List<User> Game::getUsers()
{
	List<User> users;
	users.add(this->userOne);
	users.add(this->userTwo);
	
	return users;
}

Game::~Game(void)
{
}
