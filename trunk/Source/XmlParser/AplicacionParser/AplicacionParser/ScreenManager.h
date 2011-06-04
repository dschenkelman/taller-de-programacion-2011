#pragma once
#include <string>
#include "Image.h"
#include "Pacman.h"
#include "Window.h"
#include <string>
#include "Ghost.h"
#include "List.h"
#include "Grilla.h"
#include "Activity.h"
#include "SoundManager.h"

class ScreenManager
{
	// in milliseconds
	static const int vulnerableTime = 10000;
	static const int ghostActivationTime = 4000;
	int activatedGhosts;
	int activationCycles;
	List<Ghost*> pacman1Ghosts;
	List<Ghost*> pacman2Ghosts;
	Activity* window;
	//Window* window;
	Image* fondo;
	Image* gameOverImage;
	Pacman* pacman1;
	Pacman* pacman2;
	SoundManager* soundManager;
	Uint32 period;
	int vulnerablePacman1Cycles;
	int vulnerablePacman2Cycles;
	bool pacman1GhostsVulnerable;
	bool pacman2GhostsVulnerable;
	int deadCycles;
	int imageHeight;
	int imageWidth;
	Grilla* grilla;
	Image *fondoNegro;
	void updatePacman(Pacman* pac);
	void updateGhostsVulnerability(void);
	void updateGhostsActivation(void);
	void deletePacman(Pacman* pac);
	void updateGhosts(List<Ghost*>& ghosts);
	void deleteGhosts(List<Ghost*>& ghosts);
	void createGhostsForPacman1(void);
	void createGhostsForPacman2(void);
	void handleBonusEating(Pacman* pac, List<Ghost*>& ghosts, std::string bonus, bool isPacman1);
	void deleteBonus(Pacman *pac, List<Ghost*>& ghosts, bool isPacman1);
public:
	ScreenManager(Activity* w, Image* imageFondo, Grilla* grilla, int imageHeight, int imageWidth, Uint32 period);
	//ScreenManager(Window* w, Image* imageFondo, Grilla& grilla, int imageHeight, int imageWidth);
	bool gameOver(void);
	void startGame(void);
	void handleKeyStroke(void);
	void updateScreen(void);
	~ScreenManager(void);
	List<Ghost*> getPacman1Ghosts();
	List<Ghost*> getPacman2Ghosts();
	Pacman* getPacman1();
	Pacman* getPacman2();
};
