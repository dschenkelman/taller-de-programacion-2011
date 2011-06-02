#include "StdAfx.h"
#include "Pacman.h"
#include "Image.h"
#include "Camino.h"
#include "ImageArea.h"
#include "CollisionHelper.h"
#include <string>

using namespace std;

Pacman::Pacman(string pathTexturaAbierta, string pathTexturaCerrada, Grilla& grilla, int h,
			   int w, int x, int y, int speed, int imageHeight, int imageWidth) : 
Character(pathTexturaAbierta, grilla, h, w, x, y, 0, 0, speed, imageHeight, imageWidth), dir(Direction::RIGHT),
rightKey(SDLK_RIGHT),leftKey(SDLK_LEFT), upKey(SDLK_UP), downKey(SDLK_DOWN), isDead(false),
score(0), normalBonusEaten(0), lastEatenBonus(""), ghostKills(0)
{
	this->texturaOpuesta = new Image(pathTexturaCerrada);
	this->texturaOpuesta->resize(this->imageWidth - this->speed, this->imageHeight - this->speed);
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
	if (!Character::isNextPositionValid())
	{
		Character::xDirection = 0;
		Character::yDirection = 0;
	}
	Image* aux = Character::textura;
	Character::textura = this->texturaOpuesta;
	this->texturaOpuesta = aux;
	Character::updatePosition();
}

Pacman::~Pacman(void)
{
	delete this->texturaOpuesta;
}

void Pacman::moveLeft(void)
{
	Character::moveLeft();
	switch(this->dir)
	{
		case Direction::DOWN:
			Character::textura->rotate(-90 ,0);
			this->texturaOpuesta->rotate(-90, 0);
			break;
		case Direction::UP:
			Character::textura->rotate(90 ,0);
			this->texturaOpuesta->rotate(90, 0);
			break;
		case Direction::RIGHT:
			Character::textura->rotate(180 ,0);
			this->texturaOpuesta->rotate(180, 0);
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
			this->texturaOpuesta->rotate(90, 0);
			break;
		case Direction::LEFT:
			Character::textura->rotate(180 ,0);
			this->texturaOpuesta->rotate(180, 0);
			break;
		case Direction::UP:
			Character::textura->rotate(-90 ,0);
			this->texturaOpuesta->rotate(-90, 0);
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
			this->texturaOpuesta->rotate(-90, 0);
			break;
		case Direction::LEFT:
			Character::textura->rotate(90 ,0);
			this->texturaOpuesta->rotate(90, 0);
			break;
		case Direction::UP:
			Character::textura->rotate(180 ,0);
			this->texturaOpuesta->rotate(180, 0);
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
			this->texturaOpuesta->rotate(180, 0);
			break;
		case Direction::LEFT:
			Character::textura->rotate(-90 ,0);
			this->texturaOpuesta->rotate(-90, 0);
			break;
		case Direction::RIGHT:
			Character::textura->rotate(90 ,0);
			this->texturaOpuesta->rotate(90, 0);
			break;
		default:
			break;
	}
	this->dir = Direction::UP;
}

void Pacman::kill(void)
{
	this->isDead = true;
	this->xDirection = 0;
	this->yDirection = 0;
	this->score = -10;
	Character::speed;
}

void Pacman::rotateWhenDead(void)
{
	Character::textura->rotate(90, 0);
}

bool Pacman::isAlive(void)
{
	return !this->isDead;
}

void Pacman::increaseScore(int increase)
{
	this->score += increase;
}

void Pacman::increaseEatenBonus(void)
{
	this->normalBonusEaten++;
}

int Pacman::getEatenBonus(void)
{
	return this->normalBonusEaten;
}

std::string Pacman::getLastEatenBonus(void)
{
	return this->lastEatenBonus;
}

ImageArea Pacman::eatBonus(void)
{
	int posX = this->x;
	int posY = this->y;
	int width = this->textura->getWidth();
	int height = this->textura->getHeight();

	int x1 = posX / this->imageWidth;
	int y1 = posY / this->imageHeight;
	
	int x2 = (posX + width) / this->imageWidth;
	int y2 = (posY + height) / this->imageHeight;

	if (x1 < 0 || x2 >= this->grilla.getAncho() || y1 < 0 || y2 >= this->grilla.getAlto())	{
		this->lastEatenBonus = "";
		return ImageArea(0,0,0,0);
	}

	Celda* c1 = this->grilla.getCelda(y1, x1);
	Camino* cam1 = dynamic_cast<Camino*>(c1);

	if (cam1 != NULL && cam1->hasBonus())
	{
		Image *bono=cam1->getBonus().obtenerRepresentacion();
		int posX= (x1*this->imageWidth)+(this->imageWidth-bono->getWidth())/2;
		int posY= (y1*this->imageHeight)+(this->imageHeight-bono->getHeight())/2;
		if (CollisionHelper::BonusCollision(this->textura, bono, this->x, this->y, posX, posY))
		{
			ImageArea ia(posX,posY,bono->getWidth(),bono->getHeight());
			this->lastEatenBonus = cam1->getBonus().getTipoBonus().getNombre();
			cam1->removeBonus();
			return ia;
		}
	}
	
	this->lastEatenBonus = "";
	return ImageArea(0,0,0,0);
}

void Pacman::setGhostKills(int kills)
{
	this->ghostKills = kills;
}

int Pacman::getGhostKills(void)
{
	return this->ghostKills;
}