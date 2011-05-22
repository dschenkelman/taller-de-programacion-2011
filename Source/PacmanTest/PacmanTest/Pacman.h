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
	SDLKey upKey;
	SDLKey downKey;
	SDLKey leftKey;
	SDLKey rightKey;
	int x;
	int y;
	int xDirection;
	int yDirection;
	int screenWidth;
	int screenHeight;
	static const int speed = 5;
	void moveLeft(void);
	void moveRight(void);
	void moveDown(void);
	void moveUp(void);
public:
	Pacman(std::string pathTextura, int h, int w, int x, int y);
	Image* getImage(void);
	void updatePosition(void);
	void handleKeyStroke(void);
	void changeKeyboardMappings(SDLKey up, SDLKey down, SDLKey left, SDLKey right);
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