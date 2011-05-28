#pragma once
#include <string>
#include "Image.h"
#include "Pacman.h"
#include "Window.h"
#include <string>
#include "Ghost.h"
#include "List.h"

class ScreenManager
{
	List<Ghost*> pacman1Ghosts;
	List<Ghost*> pacman2Ghosts;
	Window* window;
	Image* fondo;
	Image* gameOverImage;
	Pacman* pacman1;
	Pacman* pacman2;
	Uint32 initialTime;
	int deadCycles;
public:
	ScreenManager(Window* w, std::string pathFondo);
	void startGame(void);
	void updatePacman(Pacman* pac);
	void updateGhosts(List<Ghost*> ghosts);
	void createGhostsForPacman1(void);
	void createGhostsForPacman2(void);
	void handleKeyStroke(void);
	void updateScreen(void);
	bool gameOver(void);
	~ScreenManager(void);
};
