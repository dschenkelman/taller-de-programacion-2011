#pragma once
#include <string>
#include "Image.h"
#include "Character.h"
#include "Pacman.h"

class Ghost : public Character
{
	Pacman* pacman;
public:
	Ghost(std::string pathTextura, int h, int w, int x, int y, Pacman* pacman);
	double getDistanceToPacman(int x, int y);
	void tryKillPacman(void);
	virtual void updatePosition();
	~Ghost(void);
};
