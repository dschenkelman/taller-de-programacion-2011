#include "StdAfx.h"
#include "Pacman.h"
#include "Image.h"
#include <string>

using namespace std;

Pacman::Pacman(string pathTextura, int h, int w) : x(0), y(0), 
xDirection(0), yDirection(0), screenHeight(h), screenWidth(w), dir(Direction::RIGHT)
{
	this->textura = new Image(pathTextura);
}

void Pacman::handleKeyStroke(void)
{	
	Uint8* Keys = SDL_GetKeyState(NULL);
	
	if(Keys[SDLK_LEFT]) 	
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
	else if(Keys[SDLK_UP]) 		
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
	else if(Keys[SDLK_RIGHT]) 	
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
	else if(Keys[SDLK_DOWN]) 	
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
