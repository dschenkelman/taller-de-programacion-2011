#include "StdAfx.h"
#include "Pacman.h"
#include "Image.h"
#include "Camino.h"
#include "ImageArea.h"
#include "CollisionHelper.h"
#include <string>

using namespace std;

Pacman::Pacman(string pathTexturaAbierta, string pathTexturaCerrada, Grilla* grilla, int h,
			   int w, int x, int y, int speed, int imageHeight, int imageWidth) : 
Character(pathTexturaAbierta, grilla, h, w, x, y, 0, 0, speed, imageHeight, imageWidth), dir(Direction::RIGHT),
rightKey(SDLK_RIGHT),leftKey(SDLK_LEFT), upKey(SDLK_UP), downKey(SDLK_DOWN), isDead(false), keyPressed(Direction::CENTER), 
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
		//if (this->keyPressed == Direction::BEGIN){
		//	cout<<"KeyPressed LEFT"<<endl;
			this->keyPressed = Direction::LEFT;
		//}
		//this->moveLeft();	
	} 
	else if(Keys[this->upKey]) 		
	{ 
	/*	if (this->keyPressed == Direction::BEGIN){
			cout<<"KeyPressed UP"<<endl;
	*/		this->keyPressed = Direction::UP;
	//	}
		//this->moveUp();
	} 
	else if(Keys[this->rightKey]) 	
	{
	/*	if (this->keyPressed == Direction::BEGIN){
			cout<<"KeyPressed RIGHT"<<endl;
	*/		this->keyPressed = Direction::RIGHT;
	//	}
		//this->moveRight();
	} 
	else if(Keys[this->downKey]) 	
	{ 
	/*	if (this->keyPressed == Direction::BEGIN){
			cout<<"KeyPressed DOWN"<<endl;
	*/		this->keyPressed = Direction::DOWN;
	//	}
		//this->moveDown();
	}
}

void Pacman::updatePosition(void)
{
	
	int x=Character::xDirection;
	int y=Character::yDirection;

	
	cout<<"Key Pressed: "<<keyPressed<<endl;

	switch(this->keyPressed){
			case Direction::UP:
				Character::moveUp();
				cout<<"moveUP"<<endl;
				break;
			case Direction::DOWN:
				cout<<"moveDown"<<endl;
				Character::moveDown();
				break;
			case Direction::LEFT:
				cout<<"moveLeft"<<endl;
				Character::moveLeft();
				break;
			case Direction::RIGHT:
				cout<<"moveRight"<<endl;
				Character::moveRight();
				break;
		}
	
	if (!Character::isNextPositionValid())
	{
		cout<<"La posicion siguiente no es valida"<<endl;
		Character::xDirection = x;
		Character::yDirection = y;
		
		if (!Character::isNextPositionValid())
		{
			cout<<"La posicion original no es valida"<<endl;
			Character::xDirection = 0;
			Character::yDirection = 0;
		}
		
	}
	else
	{
		if (this->keyPressed != Direction::CENTER)
			this->rotate(this->dir,this->keyPressed);
		this->keyPressed=Direction::CENTER;
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
	this->rotate(this->dir,Direction::LEFT);
}

void Pacman::moveRight(void)
{
	Character::moveRight();
	this->rotate(this->dir,Direction::RIGHT);
}

void Pacman::moveDown(void)
{
	Character::moveDown();
	this->rotate(this->dir,Direction::DOWN);
}

void Pacman::moveUp(void)
{	
	Character::moveUp();
	this->rotate(this->dir,Direction::UP);
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

int Pacman::getScore(void)
{
	return this->score;
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

	if (x1 < 0 || x2 >= this->grilla->getAncho() || y1 < 0 || y2 >= this->grilla->getAlto())
	{
		this->lastEatenBonus = "";
		return ImageArea(0,0,0,0);
	}

	Celda* c1 = Character::grilla->getCelda(y1, x1);
	Camino* cam1 = dynamic_cast<Camino*>(c1);

	if (cam1 != NULL && cam1->hasBonus())
	{
		Image *bono=cam1->getBonus()->obtenerRepresentacion();
		int bonusWidth = bono->getWidth() > this->imageWidth ? this->imageWidth : bono->getWidth(); 
		int bonusHeight = bono->getHeight() > this->imageHeight ? this->imageHeight : bono->getHeight();
			
		int posX= (x1*this->imageWidth)+(this->imageWidth-bonusWidth)/2;
		int posY= (y1*this->imageHeight)+(this->imageHeight-bonusHeight)/2;
		if (CollisionHelper::BonusCollision(this->textura, this->x, this->y, posX, posY, bonusHeight, bonusWidth))
		{
			ImageArea ia(x1*this->imageWidth,y1*this->imageHeight,this->imageWidth,this->imageHeight);
			this->lastEatenBonus = cam1->getBonus()->getTipoBonus().getNombre();
			cam1->removeBonus();
			delete bono;
			return ia;
		}

		delete bono;
	}

	/*Celda* c2 = Character::grilla->getCelda(y2, x2);
	Camino* cam2 = dynamic_cast<Camino*>(c2);

	if (cam2 != NULL && cam2->hasBonus())
	{
		Image *bono=cam2->getBonus()->obtenerRepresentacion();
		int bonusWidth = bono->getWidth() > this->imageWidth ? this->imageWidth : bono->getWidth(); 
		int bonusHeight = bono->getHeight() > this->imageHeight ? this->imageHeight : bono->getHeight();
			
		int posX= (x2*this->imageWidth)+(this->imageWidth-bonusWidth)/2;
		int posY= (y2*this->imageHeight)+(this->imageHeight-bonusHeight)/2;
		if (CollisionHelper::BonusCollision(this->textura, this->x, this->y, posX, posY, bonusHeight, bonusWidth))
		{
			ImageArea ia(x2*this->imageWidth,y2*this->imageHeight,this->imageWidth,this->imageHeight);
			this->lastEatenBonus = cam2->getBonus()->getTipoBonus().getNombre();
			cam2->removeBonus();
			delete bono;
			return ia;
		}

		delete bono;
	}
	*/
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

void Pacman::rotate(Direction current, Direction next){
	
	if (current == next || next == Direction::CENTER)
		return;
	cout<<"A rotar de "<<current<<" a "<<next<<endl;

	switch (current){
		case Direction::UP:
			this->rotateFromUp(next);
			break;
		case Direction::DOWN:
			this->rotateFromDown(next);
			break;
		case Direction::LEFT:
			this->rotateFromLeft(next);
			break;
		case Direction::RIGHT:
			this->rotateFromRight(next);
			break;
	}
}


void Pacman::rotateFromUp( Direction next){

	cout<<"Rotate from UP: "<<next<<endl;
	switch(next)
	{
		case Direction::DOWN:
			Character::textura->rotate(180 ,0);
			this->texturaOpuesta->rotate(180, 0);
			break;
		case Direction::LEFT:
			Character::textura->rotate(90 ,0);
			this->texturaOpuesta->rotate(90, 0);
			break;
		case Direction::RIGHT:
			Character::textura->rotate(-90 ,0);
			this->texturaOpuesta->rotate(-90, 0);
			break;
		default:
			break;
	}
	this->dir =next;
}

void Pacman::rotateFromDown( Direction next){

	cout<<"Rotate from Down: "<<next<<endl;
	switch(next)
	{
		case Direction::RIGHT:
			Character::textura->rotate(90 ,0);
			this->texturaOpuesta->rotate(90, 0);
			break;
		case Direction::LEFT:
			Character::textura->rotate(-90 ,0);
			this->texturaOpuesta->rotate(-90, 0);
			break;
		case Direction::UP:
			Character::textura->rotate(180 ,0);
			this->texturaOpuesta->rotate(180, 0);
			break;
		default:
			break;
	}
	this->dir =next;
}

void Pacman::rotateFromLeft( Direction next){

	cout<<"Rotate from Left: "<<next<<endl;
	switch(next)
	{
		case Direction::DOWN:
			Character::textura->rotate(90 ,0);
			this->texturaOpuesta->rotate(90, 0);
			break;
		case Direction::UP:
			Character::textura->rotate(-90 ,0);
			this->texturaOpuesta->rotate(-90, 0);
			break;
		case Direction::RIGHT:
			Character::textura->rotate(180 ,0);
			this->texturaOpuesta->rotate(180, 0);
			break;
		default:
			break;
	}
	this->dir =  next;
}

void Pacman::rotateFromRight( Direction next){

	cout<<"Rotate from Right: "<<next<<endl;

	switch(next)
	{
		case Direction::DOWN:
			Character::textura->rotate(-90 ,0);
			this->texturaOpuesta->rotate(-90, 0);
			break;
		case Direction::LEFT:
			Character::textura->rotate(180 ,0);
			this->texturaOpuesta->rotate(180, 0);
			break;
		case Direction::UP:
			Character::textura->rotate(90 ,0);
			this->texturaOpuesta->rotate(90, 0);
			break;
		default:
			break;
	}
	this->dir =next;
}

