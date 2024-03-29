#include "StdAfx.h"
#include "Character.h"
#include "Image.h"
#include <string>
#include "Celda.h"
#include "Obstaculo.h"

using namespace std;

Character::Character(string pathTextura, Grilla* g, int h, int w, int x, int y,
					 int xDir, int yDir, int speed, int imageHeight, int imageWidth):
screenHeight(h), screenWidth(w), x(x), y(y), 
xDirection(xDir), yDirection(yDir), speed(speed),
grilla(g), imageHeight(imageHeight), imageWidth(imageWidth)
{
	this->lastX = -1;
	this->lastY = -1;
	this->grilla = g;
	this->textura = new Image(pathTextura);
	this->textura->resize(this->imageWidth - this->speed, this->imageHeight - this->speed);
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

	int x1 = (nextX / this->imageWidth) % this->grilla->getAncho();
	int y1 = (nextY / this->imageHeight) % this->grilla->getAlto();

	int x2 = ((nextX + width) / this->imageWidth) % this->grilla->getAncho();
	int y2 = ((nextY + height) / this->imageHeight) % this->grilla->getAlto();

	//if (x1 < 0 || x2 >= this->grilla->getAncho() || y1 < 0 || y2 >= this->grilla->getAlto())
	//{
	//	return false;
	//}
	Celda* c1 = this->grilla->getCelda(y1, x1);
	Celda* c2 = this->grilla->getCelda(y2, x1);
	Celda* c3 = this->grilla->getCelda(y1, x2);
	Celda* c4 = this->grilla->getCelda(y2, x2);

	Obstaculo* o1 = dynamic_cast<Obstaculo*>(c1);
	Obstaculo* o2 = dynamic_cast<Obstaculo*>(c2);
	Obstaculo* o3 = dynamic_cast<Obstaculo*>(c3);
	Obstaculo* o4 = dynamic_cast<Obstaculo*>(c4);

	if (o1 != NULL || o2 != NULL || o3 != NULL || o4 != NULL)
	{
		return false;
	}
	
	// TODO: Implementar logica para ver si a donde me quiero mover no hay un obstaculo
	return true;
}

void Character::updatePosition(void)
{
	this->lastX = this->x;
	this->lastY = this->y;
	this->x = this->getNextX();
	this->y = this->getNextY();
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