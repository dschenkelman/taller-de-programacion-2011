#pragma once

#include "Image.h"
#include <string>
#include "Character.h"

class Pacman : public Character
{
	enum Direction
	{
		RIGHT,
		LEFT,
		UP,
		DOWN
	};
	Image* texturaOpuesta;
	Direction dir;
	SDLKey upKey;
	SDLKey downKey;
	SDLKey leftKey;
	SDLKey rightKey;
	bool isDead;
	virtual void moveLeft(void);
	virtual void moveRight(void);
	virtual void moveDown(void);
	virtual void moveUp(void);
	double* getDistancesForEachPosition(void);
public:
	Pacman(std::string pathTexturaAbierta, std::string pathTexturaCerrada,int h, int w, int x, int y, int speed);
	void handleKeyStroke(void);
	void changeKeyboardMappings(SDLKey up, SDLKey down, SDLKey left, SDLKey right);
	virtual void updatePosition(void);
	void rotateWhenDead(void);
	void kill(void);
	bool isAlive(void);
	~Pacman(void);
};