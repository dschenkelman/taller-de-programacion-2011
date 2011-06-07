#include "StdAfx.h"
#include "Ghost.h"
#include <string>
#include "math.h"
#include <algorithm>
#include "CollisionHelper.h"
#include <vector>
#include <limits>
#include "Obstaculo.h"
#include "Celda.h"

using namespace std;

Ghost::Ghost(SoundManager* soundManager, string pathTextura, string pathTexturaVulnerable, Grilla* grilla, int h, int w, 
			 int x, int y, int speed, Pacman* pacman, int imageHeight, int imageWidth, bool inHq, int idiotCorner):
Character(pathTextura, grilla, h, w, x, y, 0, 0, speed, imageHeight, imageWidth), pacman(pacman), 
pathTextura(pathTextura), pathTexturaVulnerable(pathTexturaVulnerable),
isVulnerable(false), originalSpeed(speed), originalX(x), originalY(y), 
inHeadquarters(inHq), isActive(false), idiotMode(false), idiotCorner(idiotCorner),
outXPosition(0), outYPosition(0)
{
	this->soundManager = soundManager;
	this->outXPosition = this->imageWidth * ((grilla->getAncho() - 1) / 2);
	this->outYPosition = ((this->imageHeight * (this->grilla->getAlto() - 1)) / 2) - 24;
	this->texturaNoVulnerable = this->textura;
	this->texturaVulnerable = new Image(this->pathTexturaVulnerable);
	this->texturaVulnerable->resize(this->imageWidth - this->speed, this->imageHeight - this->speed);
	this->moveHistoryPos = 0;
	this->moveHistory[0] = 999;
}

void Ghost::updatePosition(void)
{
	if (this->isActive)
	{
		if (this->inHeadquarters)
		{
			double distance = this->getDistanceToLeaveHeadquarters(Character::x, Character::y);
			if (distance < 1.5)
			{
				this->inHeadquarters = false;
				this->idiotMode=true;
			}
		}
		this->determineNextPosition();
		Character::updatePosition();
	}

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

double Ghost::getDistanceToLeaveHeadquarters(int x, int y)
{
	int xDif = x - this->outXPosition;
	int yDif = y - this->outYPosition;
	double dif = xDif * xDif + yDif * yDif;
	double distance = sqrt(dif);
	return distance;
}

double Ghost::getDistanceToCorner(int x, int y)
{
	//return Ghost::getDistanceToLeaveHeadquarters(x,y);
	int xOffset, yOffset;
	if (this->idiotCorner%2) xOffset = 500;
	else xOffset = 0;
	if (this->idiotCorner<2) yOffset = 500;
	else yOffset = 0;
	int xDif = x - xOffset;
	int yDif = y - yOffset;
	double dif = xDif * xDif + yDif * yDif;
	double distance = sqrt(dif);
	return distance;
}

void Ghost::setIsVulnerable(bool value)
{
	if (value != this->isVulnerable)
	{
		this->isVulnerable = value;
		if (this->isVulnerable)
		{
			Character::textura = this->texturaVulnerable;
			Character::speed = this->originalSpeed * 2 / 3;
		}
		else
		{
			Character::textura = this->texturaNoVulnerable;
			Character::speed = this->originalSpeed;
		}
	}
}

void Ghost::setIsActive(bool value)
{
	this->isActive = value;
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
			int ghostKills = this->pacman->getGhostKills();
			ghostKills++;
			this->pacman->setGhostKills(ghostKills);
			this->pacman->increaseScore(200 * ghostKills);
			this->soundManager->playSound(this->soundManager->getEatGhostPath(), 1);
		}
		else
		{
			this->pacman->kill();
		}
	}
}

int getDiferentPositions(int posArray[], int size) {
	int ret = 0;
	for (int i=0;i<4;i++) {
		for (int j=0;j<size;j++) {
			if (posArray[j]==i) {
				ret++;
				break;
			}
		}
	}
	return ret;
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
			this->idiotMode=false;
			this->idiotModeTimeout=0;
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
		if (!this->moveHistory[this->moveHistoryPos] == position) {
			this->moveHistory[this->moveHistoryPos] = position;
			this->moveHistoryPos++;
			if (this->moveHistoryPos>3) this->moveHistoryPos=0;
		}
		if (getDiferentPositions(this->moveHistory,4) == 2 && this->idiotModeTimeout < 100 ) {
			if (!this->idiotMode) {
				this->idiotMode = true;
			}
			/*this->idiotMode = true;*/
			this->idiotModeTimeout++;
		} else {
			if (this->idiotMode) {
				this->moveHistory[0]=0;
				this->moveHistory[1]=1;
				this->moveHistory[2]=2;
				this->moveHistory[3]=3;
			}
			this->idiotMode = false;
			this->idiotModeTimeout = 0;
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
	} while(!this->isNextPositionValid() && attempts < 4);
}

void Ghost::rotateLeft(void)
{
	if (this->xDirection==0 && this->yDirection==0) {
		this->xDirection=-1;
		this->yDirection=0;
		return;
	}
	int tmp = this->xDirection;
	this->xDirection = this->yDirection;
	this->yDirection = tmp;
	if (this->xDirection==0) this->yDirection = -this->yDirection;
}

vector<double> Ghost::getDistanceForEachPosition(void)
{
	vector<double> distances;
	double distanceUp;
	double distanceDown;
	double distanceLeft;
	double distanceRight;

	if (!this->inHeadquarters)
	{
		if(!this->idiotMode) {
			distanceUp = this->getDistanceToPacman(Character::x, Character::y - Character::speed);
			distanceDown = this->getDistanceToPacman(Character::x, Character::y + Character::speed);
			distanceLeft = this->getDistanceToPacman(Character::x - Character::speed, Character::y);
			distanceRight = this->getDistanceToPacman(Character::x + Character::speed, Character::y);
		} else {
			distanceUp = this->getDistanceToCorner(Character::x, Character::y - Character::speed);
			distanceDown = this->getDistanceToCorner(Character::x, Character::y + Character::speed);
			distanceLeft = this->getDistanceToCorner(Character::x - Character::speed, Character::y);
			distanceRight = this->getDistanceToCorner(Character::x + Character::speed, Character::y);
		}
	}
	else
	{
		distanceUp = this->getDistanceToLeaveHeadquarters(Character::x, Character::y - Character::speed);
		distanceDown = this->getDistanceToLeaveHeadquarters(Character::x, Character::y + Character::speed);
		distanceLeft = this->getDistanceToLeaveHeadquarters(Character::x - Character::speed, Character::y);
		distanceRight = this->getDistanceToLeaveHeadquarters(Character::x + Character::speed, Character::y);
	}

	distances.push_back(distanceUp);
	distances.push_back(distanceDown);
	distances.push_back(distanceLeft);
	distances.push_back(distanceRight);

	return distances;
}

void Ghost::comeBackToLife(void)
{
	Character::x = (this->imageWidth * (this->grilla->getAncho() - 1)) / 2;
	Character::y = ((this->imageHeight * (this->grilla->getAlto() - 1)) / 2) + this->imageHeight;
	this->setIsVulnerable(false);
	this->inHeadquarters = true;
	this->idiotMode = false;
}

bool Ghost::isNextPositionValid(void)
{
	bool defaultValid = Character::isNextPositionValid();

	if (!defaultValid)
	{
		if (this->inHeadquarters)
		{
			bool goingOut = this->isGoingThroughDoor();
			return goingOut;
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool Ghost::isGoingThroughDoor(void)
{
	int nextX = this->getNextX();
	int nextY = this->getNextY();
	int width = this->textura->getWidth();
	int height = this->textura->getHeight();

	int x1 = nextX / this->imageWidth;
	int y1 = nextY / this->imageHeight;

	int x2 = (nextX + width) / this->imageWidth;
	int y2 = (nextY + height) / this->imageHeight;

	if (x1 < 0 || x2 >= this->grilla->getAncho() || y1 < 0 || y2 >= this->grilla->getAlto())
	{
		return false;
	}
	Celda* c1 = this->grilla->getCelda(y1, x1);
	Celda* c2 = this->grilla->getCelda(y2, x1);
	Celda* c3 = this->grilla->getCelda(y1, x2);
	Celda* c4 = this->grilla->getCelda(y2, x2);

	Obstaculo* o1 = dynamic_cast<Obstaculo*>(c1);
	Obstaculo* o2 = dynamic_cast<Obstaculo*>(c2);
	Obstaculo* o3 = dynamic_cast<Obstaculo*>(c3);
	Obstaculo* o4 = dynamic_cast<Obstaculo*>(c4);

	bool a = (o1 == NULL || (o1 != NULL && o1->getTipoObstaculo().getNombre() == "puerta"));
	bool b = (o2 == NULL || (o2 != NULL && o2->getTipoObstaculo().getNombre() == "puerta"));
	bool c = (o3 == NULL || (o3 != NULL && o3->getTipoObstaculo().getNombre() == "puerta"));
	bool d = (o4 == NULL || (o4 != NULL && o4->getTipoObstaculo().getNombre() == "puerta"));

	return a && b && c && d;
}

Ghost::~Ghost(void)
{
	if (this->isVulnerable)
	{
		delete this->texturaNoVulnerable;
	}
	else
	{
		delete this->texturaVulnerable;
	}
}
