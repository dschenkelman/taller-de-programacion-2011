#pragma once
#include <string>
#include "Image.h"
#include "Character.h"
#include "Pacman.h"
#include <vector>
#include <stack>
#include "SoundManager.h"

class Ghost : public Character
{
	SoundManager* soundManager;
	Image* texturaVulnerable;
	Image* texturaNoVulnerable;
	Pacman* pacman;
	static const int pacmanKillDelta = 5;
	bool isVulnerable;
	bool idiotMode;
	int idiotCorner;
	int moveHistory[4];
	int moveHistoryPos;
	int idiotModeTimeout;
	std::string pathTextura;
	std::string pathTexturaVulnerable;
	int originalSpeed;
	int originalX;
	int originalY;
	// represent the cell just above the HQ
	int outXPosition;
	int outYPosition;
	void determineNextPosition(void);
	std::vector<double> getDistanceForEachPosition(void);
	bool inHeadquarters;
	virtual bool isNextPositionValid(void);
	bool isGoingThroughDoor(void);
	bool isActive;
public:
	Ghost(SoundManager* soundManager, std::string pathTextura, std::string texturaVulnerable,
		Grilla* grilla, int h, int w, int x, int y, int speed, 
		Pacman* pacman, int imageHeight, int imageWidth, bool inHq, int idiotCorner);
	double getDistanceToPacman(int x, int y);
	double getDistanceToLeaveHeadquarters(int x, int y);
	double getDistanceToCorner(int x, int y);
	void checkPacmanCollision(void);
	void comeBackToLife(void);
	void setIsVulnerable(bool vulnerable);
	void setIsActive(bool value);
	virtual void updatePosition();
	void rotateLeft(void);
	void setPacman(Pacman* pac);
	~Ghost(void);
};
