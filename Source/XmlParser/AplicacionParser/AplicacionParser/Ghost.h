#pragma once
#include <string>
#include "Image.h"
#include "Character.h"
#include "Pacman.h"
#include <vector>

class Ghost : public Character
{
	Image* texturaVulnerable;
	Image* texturaNoVulnerable;
	Pacman* pacman;
	static const int pacmanKillDelta = 5;
	bool isVulnerable;
	std::string pathTextura;
	std::string pathTexturaVulnerable;
	int originalSpeed;
	int originalX;
	int originalY;
	void determineNextPosition(void);
	std::vector<double> getDistanceForEachPosition(void);
public:
	Ghost(std::string pathTextura, std::string texturaVulnerable,
		Grilla& grilla, int h, int w, int x, int y, int speed, Pacman* pacman, int imageHeight, int imageWidth);
	double getDistanceToPacman(int x, int y);
	void checkPacmanCollision(void);
	void comeBackToLife(void);
	void setIsVulnerable(bool vulnerable);
	virtual void updatePosition();
	~Ghost(void);
};
