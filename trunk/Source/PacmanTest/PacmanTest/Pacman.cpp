#include "StdAfx.h"
#include "Pacman.h"
#include "Image.h"
#include <string>

using namespace std;

Pacman::Pacman(string pathTextura, int h, int w, int x, int y) : 
Character(pathTextura, h, w, x, y, 0, 0), dir(Direction::RIGHT),
rightKey(SDLK_RIGHT),leftKey(SDLK_LEFT), upKey(SDLK_UP), downKey(SDLK_DOWN)
{
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

Pacman::~Pacman(void)
{
}

void Pacman::moveLeft(void)
{
	Character::moveLeft();
	switch(this->dir)
	{
		case Direction::DOWN:
			Character::textura->rotate(-90 ,0);
			break;
		case Direction::UP:
			Character::textura->rotate(90 ,0);
			break;
		case Direction::RIGHT:
			Character::textura->rotate(180 ,0);
			break;
		default:
			break;
	}
	this->dir = Direction::LEFT;
}

void Pacman::moveRight(void)
{
	Character::moveRight();
	switch(this->dir)
	{
		case Direction::DOWN:
			Character::textura->rotate(90 ,0);
			break;
		case Direction::LEFT:
			Character::textura->rotate(180 ,0);
			break;
		case Direction::UP:
			Character::textura->rotate(-90 ,0);
			break;
		default:
			break;
	}
	this->dir = Direction::RIGHT;
}

void Pacman::moveDown(void)
{
	Character::moveDown();
	switch(this->dir)
	{
		case Direction::RIGHT:
			Character::textura->rotate(-90 ,0);
			break;
		case Direction::LEFT:
			Character::textura->rotate(90 ,0);
			break;
		case Direction::UP:
			Character::textura->rotate(180 ,0);
			break;
		default:
			break;
	}
	this->dir = Direction::DOWN;
}

void Pacman::moveUp(void)
{	
	Character::moveUp();
	switch(this->dir)
	{
		case Direction::DOWN:
			Character::textura->rotate(180 ,0);
			break;
		case Direction::LEFT:
			Character::textura->rotate(-90 ,0);
			break;
		case Direction::RIGHT:
			Character::textura->rotate(90 ,0);
			break;
		default:
			break;
	}
	this->dir = Direction::UP;
}