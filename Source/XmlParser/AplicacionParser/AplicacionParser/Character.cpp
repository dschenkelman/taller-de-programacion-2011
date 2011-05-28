#include "StdAfx.h"
#include "Character.h"
#include "Image.h"
#include <string>
#include "Celda.h"

using namespace std;

Character::Character(string pathTextura, Grilla& grilla, int h, int w, int x, int y,
					 int xDir, int yDir, int speed, int imageHeight, int imageWidth):
screenHeight(h), screenWidth(w), x(x), y(y), 
xDirection(xDir), yDirection(yDir), speed(speed),
grilla(grilla), imageHeight(imageHeight), imageWidth(imageWidth)
{
	this->textura = new Image(pathTextura);
}

void Character::moveDown(void)
{
	this->xDirection = 0;
	this->yDirection = 1;
}

void Character::moveLeft(void)
{
	this->xDirection = -1;
	this->yDirection = 0;
}

void Character::moveUp(void)
{
	this->xDirection = 0;
	this->yDirection = -1;
}

void Character::moveRight(void)
{
	this->xDirection = 1;
	this->yDirection = 0;
}

bool Character::isNextPositionValid(void)
{
	int nextX = this->getNextX();
	int nextY = this->getNextY();
	int width = this->textura->getWidth();
	int height = this->textura->getHeight();

	int x1 = nextX / this->imageWidth;
	int y1 = nextY / this->imageHeight;

	int x2 = (nextX + width) / this->imageWidth;
	int y2 = (nextY + height) / this->imageHeight;

	if (x1 < 0 || x2 >= this->grilla.getAncho() || y1 < 0 || y2 >= this->grilla.getAlto())
	{
		return false;
	}
	Celda* c1 = this->grilla.getCelda(y1, x1);
	Celda* c2 = this->grilla.getCelda(y2, x1);
	Celda* c3 = this->grilla.getCelda(y1, x2);
	Celda* c4 = this->grilla.getCelda(y2, x2);
	// TODO: Implementar logica para ver si a donde me quiero mover no hay un obstaculo
	return true;
}

void Character::updatePosition(void)
{
	Character::x = this->getNextX();
	Character::y = this->getNextY();
}

int Character::getNextX(void)
{
	int nextX = (Character::x + (Character::speed * Character::xDirection)) % Character::screenWidth;
	if (nextX < 0)
	{
		nextX = Character::screenWidth - 1;
	}

	return nextX;
}

int Character::getNextY(void)
{
	int nextY = (this->y + (Character::speed * Character::yDirection)) % Character::screenHeight;

	if (nextY < 0)
	{
		nextY = Character::screenHeight - 1;
	}

	return nextY;
}

Character::~Character(void)
{
	delete this->textura;
}