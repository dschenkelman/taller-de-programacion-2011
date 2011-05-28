#include "StdAfx.h"
#include "Ghost.h"
#include <string>
#include "math.h"
#include <algorithm>
#include "CollisionHelper.h"
#include <vector>
#include <limits>

using namespace std;

Ghost::Ghost(string pathTextura, string texturaVulnerable, int h, int w, int x, int y, int speed, Pacman* pacman):
Character(pathTextura, h, w, x, y, 0, 0, speed), pacman(pacman), 
pathTextura(pathTextura), texturaVulnerable(texturaVulnerable),
isVulnerable(false), originalSpeed(speed), originalX(x), originalY(y)
{
}

void Ghost::updatePosition(void)
{
	this->determineNextPosition();
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

void Ghost::determineNextPosition(void)
{
	// 4 possible positions, array of 4
	vector<double> distances = this->getDistanceForEachPosition();
	int attempts = 0;
	do
	{
		int position;	
		if (this->isVulnerable)
		{
			// runaway
			position = max_element(distances.begin(), distances.end()) - distances.begin();
			
			// to avoid taking this into account if the position is not valid
			distances[position] = 0;
		}
		else
		{
			// chase
			position = min_element(distances.begin(), distances.end()) - distances.begin();
			
			// to avoid taking this into account if the position is not valid
			distances[position] = numeric_limits<double>::max();
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

		attempts++;
	} while(!Character::isNextPositionValid() && attempts < 4);
}

vector<double> Ghost::getDistanceForEachPosition(void)
{
	vector<double> distances;
	double distanceUp = this->getDistanceToPacman(Character::x, Character::y - Character::speed);
	double distanceDown = this->getDistanceToPacman(Character::x, Character::y + Character::speed);
	double distanceLeft = this->getDistanceToPacman(Character::x - Character::speed, Character::y);
	double distanceRight = this->getDistanceToPacman(Character::x + Character::speed, Character::y);

	distances.push_back(distanceUp);
	distances.push_back(distanceDown);
	distances.push_back(distanceLeft);
	distances.push_back(distanceRight);

	return distances;
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
