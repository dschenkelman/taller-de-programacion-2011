#pragma once

#include "Image.h"
#include <string>
#include "Character.h"
#include "ImageArea.h"

class Pacman : public Character
{
	enum Direction
	{
		RIGHT,
		LEFT,
		UP,
		DOWN,
		CENTER
	};
	Image* texturaOpuesta;
	Direction dir;
	SDLKey upKey;
	SDLKey downKey;
	SDLKey leftKey;
	SDLKey rightKey;

	Direction keyPressed;

	bool isDead;
	virtual void moveLeft(void);
	virtual void moveRight(void);
	virtual void moveDown(void);
	virtual void moveUp(void);
	double* getDistancesForEachPosition(void);
	std::string lastEatenBonus;
	int score;
	int normalBonusEaten;
	int ghostKills;
	void rotate(Direction current, Direction next);
	void rotateFromUp( Direction next);
	void rotateFromDown( Direction next);
	void rotateFromLeft( Direction next);
	void rotateFromRight( Direction next);
public:
	Pacman(std::string pathTexturaAbierta, std::string pathTexturaCerrada, Grilla* grilla, 
		int h, int w, int x, int y, int speed, int imageHeight, int imageWidth);
	void handleKeyStroke(void);
	void changeKeyboardMappings(SDLKey up, SDLKey down, SDLKey left, SDLKey right);
	virtual void updatePosition(void);
	void rotateWhenDead(void);
	void kill(void);
	bool isAlive(void);
	void increaseScore(int increase);
	int getScore(void);
	void increaseEatenBonus(void);
	int getEatenBonus(void);
	int getGhostKills(void);
	void setGhostKills(int kills);
	std::string getLastEatenBonus(void);
	ImageArea eatBonus(void);
	~Pacman(void);
};