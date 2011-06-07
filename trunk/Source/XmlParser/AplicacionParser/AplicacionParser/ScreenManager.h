#pragma once
#include <string>
#include "Image.h"
#include "Pacman.h"
#include "Window.h"
#include <string>
#include <map>
#include "Ghost.h"
#include "List.h"
#include "Grilla.h"
#include "Activity.h"
#include "SoundManager.h"
#include "SpecialBonusManager.h"

class ScreenManager
{
	// in milliseconds
	static const int vulnerableTime = 10000;
	static const int ghostActivationTime = 4000;
	
	List<Ghost*> pacman1Ghosts;
	List<Ghost*> pacman2Ghosts;
	std::map<std::string, int> activeBonusPacman1;
	std::map<std::string, int> activeBonusPacman2;
	Activity* window;
	//Window* window;
	bool finished;
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
	int boardHeight;
	int boardWidth;
	int pasosTotales;
	Grilla* grilla;
	Image *fondoNegro;
	int originalPacmanSpeed;
	
	Image* specialBonusImage;
	int specialBonusX;
	int specialBonusY;
	SpecialBonusManager sbm;
	int activatedGhosts;
	int activationCycles;
	int bonusAppearenceCycles;
	bool bonusShowing;
	TipoBonus bonusToShow;
	int bonusAppearenceInterval;
	int bonusLastingInterval;

	void updatePacman(Pacman* pac);
	void updateGhostsVulnerability(void);
	void updateGhostsActivation(void);
	void deletePacman(Pacman* pac);
	void updateGhosts(List<Ghost*>& ghosts);
	void deleteGhosts(List<Ghost*>& ghosts);
	void createGhostsForPacman1(void);
	void createGhostsForPacman2(void);
	void handleNormalBonusEating(Pacman* pac, List<Ghost*>& ghosts, std::string bonus, bool isPacman1);
	void handleSpecialBonusEating(Pacman* pac, List<Ghost*>& ghosts, std::string bonus, bool isPacman1);
	void handleCollisionWithOppositeCharacters(Pacman* pac, Pacman* opponent, List<Ghost*>& opponentGhosts);
	void assignPacmanToGhosts(List<Ghost*>& ghosts, Pacman* pac);
	void deleteBonus(Pacman *pac, List<Ghost*>& ghosts, bool isPacman1);
	void loadSpecialBonus(void);
	void updateSpecialBonus(void);
	void updateBonusEffects(Pacman* pac, Pacman* op, List<Ghost*>& ghosts);
	void cancelBonusEffect(std::string bonusType, Pacman* pac, Pacman* op, List<Ghost*>& ghosts);
	void increasePacmanScore(Pacman* pac, bool isPacman1, int score);
	bool isFoodOver(void);
	void placeBonusInMaze(TipoBonus& bonus);
	void removeBonusFromMaze(void);
	void bonusInitialization(void);
public:
	ScreenManager(Activity* w, Image* imageFondo, Grilla* grilla, int imageHeight,
		int imageWidth, Uint32 period, int bonusInterval, double lastingProportion);
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
