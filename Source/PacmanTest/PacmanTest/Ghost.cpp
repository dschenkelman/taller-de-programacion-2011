#include "StdAfx.h"
#include "Ghost.h"
#include <string>
#include "math.h"
#include <algorithm>
#include "CollisionHelper.h"

using namespace std;

Ghost::Ghost(string pathTextura, string texturaVulnerable, int h, int w, int x, int y, int speed, Pacman* pacman):
Character(pathTextura, h, w, x, y, 0, 0, speed), pacman(pacman), 
pathTextura(pathTextura), texturaVulnerable(texturaVulnerable),
isVulnerable(false), originalSpeed(speed), originalX(x), originalY(y)
{
}

void Ghost::updatePosition(void)
{
	double distanceUp = this->getDistanceToPacman(Character::x, Character::y - Character::speed);
	double distanceDown = this->getDistanceToPacman(Character::x, Character::y + Character::speed);
	double distanceLeft = this->getDistanceToPacman(Character::x - Character::speed, Character::y);
	double distanceRight = this->getDistanceToPacman(Character::x + Character::speed, Character::y);

	double distances[4] = {distanceUp, distanceDown, distanceLeft, distanceRight};

	int position;
	if (this->isVulnerable)
	{
		// runaway
		position = max_element(distances, distances + 4) - distances;
	}
	else
	{
		// chase
		position = min_element(distances, distances + 4) - distances;
	}

	switch(position)
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
	this->checkPacmanCollision();
}

double Ghost::getDistanceToPacman(int x, int y)
{
	if (x < 0)
	{
		x += Character::screenWidth;
	}

	if (y < 0)
	{
		y += Character::screenHeight;
	}

	int xDif = abs((x % Character::screenWidth) - this->pacman->getX());
	int yDif = abs((y % Character::screenHeight) - this->pacman->getY());
	double dif = xDif * xDif + yDif * yDif;
	double distance = sqrt(dif);
	return distance;
}

void Ghost::setIsVulnerable(bool value)
{
	if (value != this->isVulnerable)
	{
		this->isVulnerable = value;
		delete Character::textura;
		if (this->isVulnerable)
		{
			Character::textura = new Image(this->texturaVulnerable);
			Character::speed = this->originalSpeed * 2 / 3;
		}
		else
		{
			Character::textura = new Image(this->pathTextura);
			Character::speed = this->originalSpeed;
		}
	}
}

void Ghost::checkPacmanCollision(void)
{
	bool areInSamePosition = CollisionHelper::AreFullyCollisioned(Character::x, Character::y,
		this->pacman->getX(), this->pacman->getY(), 2);

	areInSamePosition = areInSamePosition || CollisionHelper::AreFullyCollisioned(Character::x + Character::textura->getWidth(), Character::y + Character::textura->getHeight(),
		this->pacman->getX() + this->pacman->getImage()->getWidth(), this->pacman->getY() + this->pacman->getImage()->getHeight(), pacmanKillDelta);

	if (areInSamePosition)
	{
		if (this->isVulnerable)
		{
			this->comeBackToLife();
		}
		else
		{
			this->pacman->kill();
		}
	}
}

void Ghost::comeBackToLife(void)
{
	Character::x = this->originalX;
	Character::y = this->originalY;
	this->setIsVulnerable(false);
}

Ghost::~Ghost(void)
{
}
