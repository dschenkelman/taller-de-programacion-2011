#include "StdAfx.h"
#include "Character.h"
#include "Image.h"
#include <string>

using namespace std;

Character::Character(string pathTextura, int h, int w, int x, int y, int xDir, int yDir, int speed):
screenHeight(h), screenWidth(w), x(x), y(y), xDirection(xDir), yDirection(yDir), speed(speed)
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
	// TODO: Implementar logica para ver si a donde me quiero mover no hay un obstaculo
	return true;
}

void Character::updatePosition(void)
{
	Character::x = (Character::x + (Character::speed * Character::xDirection)) % Character::screenWidth;
	if (Character::x < 0)
	{
		Character::x = Character::screenWidth - 1;
	}

	Character::y = (this->y + (Character::speed * Character::yDirection)) % Character::screenHeight;

	if (Character::y < 0)
	{
		Character::y = Character::screenHeight - 1;
	}
}

Character::~Character(void)
{
	delete this->textura;
}
