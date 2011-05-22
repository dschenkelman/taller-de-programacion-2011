#pragma once
#include "Image.h"
#include <string>


class Character
{
protected:
	Image* textura;
	int x;
	int y;
	int xDirection;
	int yDirection;
	int screenWidth;
	int screenHeight;
	static const int speed = 5;
	virtual void moveLeft(void);
	virtual void moveRight(void);
	virtual void moveDown(void);
	virtual void moveUp(void);
	Character(std::string pathTextura, int h, int w, int x, int y, int xDir, int yDir);
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
