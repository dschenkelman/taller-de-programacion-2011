#pragma once

#include "Image.h"
#include <string>


class Pacman
{
	enum Direction
	{
		RIGHT,
		LEFT,
		UP,
		DOWN
	};
	Image* textura;
	Direction dir;
	int x;
	int y;
	int xDirection;
	int yDirection;
	int screenWidth;
	int screenHeight;
	static const int speed = 5;
public:
	Pacman(std::string pathTextura, int h, int w);
	Image* getImage(void);
	void updatePosition(void);
	void handleKeyStroke(void);
	int getX()
	{
		return this->x;
	}
	int getY()
	{
		return this->y;
	}
	~Pacman(void);
};