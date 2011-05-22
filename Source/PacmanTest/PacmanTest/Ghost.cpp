#include "StdAfx.h"
#include "Ghost.h"
#include <string>
#include "math.h"
#include <algorithm>

using namespace std;

Ghost::Ghost(string pathTextura, int h, int w, int x, int y, Pacman* pacman):
Character(pathTextura, h, w, x, y, 0, 0), pacman(pacman)
{
}

void Ghost::updatePosition(void)
{
	double distanceUp = this->getDistanceToPacman(Character::x, Character::y-1);
	double distanceDown = this->getDistanceToPacman(Character::x, Character::y+1);
	double distanceLeft = this->getDistanceToPacman(Character::x - 1, Character::y);
	double distanceRight = this->getDistanceToPacman(Character::x + 1, Character::y);

	double distances[4] = {distanceUp, distanceDown, distanceLeft, distanceRight};

	int minPosition = min_element(distances, distances + 4) - distances;
	switch(minPosition)
	{
		case 0:
			Character::moveUp();
			break;
		case 1:
			Character::moveDown();
			break;
		case 2:
			Character::moveLeft();
			break;
		case 3:
			Character::moveRight();
			break;
	}

	Character::updatePosition();
}

double Ghost::getDistanceToPacman(int x, int y)
{
	int xDif = abs(x - this->pacman->getX());
	int yDif = abs(y - this->pacman->getY());
	double dif = xDif * xDif + yDif * yDif;
	double distance = sqrt(dif);
	return distance;
}

void Ghost::tryKillPacman(void)
{

}

Ghost::~Ghost(void)
{
}
