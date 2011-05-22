#include "StdAfx.h"
#include "Pacman.h"
#include "Image.h"
#include <string>

using namespace std;

Pacman::Pacman(string pathTextura, int h, int w, int x, int y) : x(x), y(y), 
xDirection(0), yDirection(0), screenHeight(h), screenWidth(w), dir(Direction::RIGHT),
rightKey(SDLK_RIGHT),leftKey(SDLK_LEFT), upKey(SDLK_UP), downKey(SDLK_DOWN)
{
	this->textura = new Image(pathTextura);
}

void Pacman::changeKeyboardMappings(SDLKey up, SDLKey down, SDLKey left, SDLKey right)
{
	this->upKey = up;
	this->downKey = down;
	this->leftKey = left;
	this->rightKey = right;
}

void Pacman::handleKeyStroke(void)
{	
	Uint8* Keys = SDL_GetKeyState(NULL);
	
	if(Keys[this->leftKey]) 	
	{
		this->moveLeft();	
	} 
	else if(Keys[this->upKey]) 		
	{ 
		this->moveUp();
	} 
	else if(Keys[this->rightKey]) 	
	{
		this->moveRight();
	} 
	else if(Keys[this->downKey]) 	
	{ 
		this->moveDown();
	}
}

void Pacman::updatePosition(void)
{
	this->x = (this->x + (this->speed * this->xDirection)) % this->screenWidth;
	if (this->x < 0)
	{
		this->x = this->screenWidth - 1;
	}

	this->y = (this->y + (this->speed * this->yDirection)) % this->screenHeight;

	if (this->y < 0)
	{
		this->y = this->screenHeight - 1;
	}
}

Image* Pacman::getImage(void)
{
	return this->textura;
}

Pacman::~Pacman(void)
{
	delete this->textura;
}

void Pacman::moveLeft(void)
{
	this->xDirection = -1;
	this->yDirection = 0;
	switch(this->dir)
	{
		case Direction::DOWN:
			this->textura->rotate(-90 ,0);
			break;
		case Direction::UP:
			this->textura->rotate(90 ,0);
			break;
		case Direction::RIGHT:
			this->textura->rotate(180 ,0);
			break;
		default:
			break;
	}
	this->dir = Direction::LEFT;
}

void Pacman::moveRight(void)
{
	this->xDirection = 1;
	this->yDirection = 0;
	switch(this->dir)
	{
		case Direction::DOWN:
			this->textura->rotate(90 ,0);
			break;
		case Direction::LEFT:
			this->textura->rotate(180 ,0);
			break;
		case Direction::UP:
			this->textura->rotate(-90 ,0);
			break;
		default:
			break;
	}
	this->dir = Direction::RIGHT;
}

void Pacman::moveDown(void)
{
	this->xDirection = 0;
	this->yDirection = 1;
	switch(this->dir)
	{
		case Direction::RIGHT:
			this->textura->rotate(-90 ,0);
			break;
		case Direction::LEFT:
			this->textura->rotate(90 ,0);
			break;
		case Direction::UP:
			this->textura->rotate(180 ,0);
			break;
		default:
			break;
	}
	this->dir = Direction::DOWN;
}

void Pacman::moveUp(void)
{
	this->xDirection = 0;
		this->yDirection = -1;
		switch(this->dir)
		{
			case Direction::DOWN:
				this->textura->rotate(180 ,0);
				break;
			case Direction::LEFT:
				this->textura->rotate(-90 ,0);
				break;
			case Direction::RIGHT:
				this->textura->rotate(90 ,0);
				break;
			default:
				break;
		}
		this->dir = Direction::UP;
}