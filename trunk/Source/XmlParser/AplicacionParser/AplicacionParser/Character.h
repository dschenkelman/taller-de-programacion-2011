#pragma once
#include "Image.h"
#include <string>
#include "Grilla.h"

class Character
{
	int getNextX(void);
	int getNextY(void);
protected:
	Image* textura;
	Grilla& grilla;
	int x;
	int y;
	int xDirection;
	int yDirection;
	int screenWidth;
	int screenHeight;
	int speed;
	int imageHeight;
	int imageWidth;
	virtual void moveLeft(void);
	virtual void moveRight(void);
	virtual void moveDown(void);
	virtual void moveUp(void);
	bool isNextPositionValid(void);
	Character(std::string pathTextura, Grilla& grilla, int h, int w, int x, int y, int xDir, int yDir, int speed, int imageHeight, int imageWidth);
public:
	virtual void updatePosition(void);
	Image* getImage(void)
	{
		return this->textura;
	}
	int getX()
	{
		return this->x;
	}
	int getY()
	{
		return this->y;
	}
	virtual ~Character(void);
};
