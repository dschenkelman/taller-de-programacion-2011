#include "StdAfx.h"
#include "ScreenManager.h"
#include "Pacman.h"
#include "Window.h"
#include "ImageArea.h"
#include "Camino.h"
#include <string>
#include "CollisionHelper.h"

using namespace std;

ScreenManager::ScreenManager(Activity* w, Image* imageFondo, Grilla* g, 
							 int imageHeight, int imageWidth, Uint32 period,
							 int bonusInterval, double lastingProportion) 

							 : deadCycles(0), imageHeight(imageHeight), imageWidth(imageWidth), period(period),
vulnerablePacman1Cycles(0), vulnerablePacman2Cycles(0), 
pacman1GhostsVulnerable(false), pacman2GhostsVulnerable(false),
activatedGhosts(0), activationCycles(ghostActivationTime), bonusAppearenceCycles(0), 
bonusShowing(false), finished(false), specialBonusX(0), specialBonusY(0), playedOpeningSong(false)
{
	this->soundManager = new SoundManager();
	this->specialBonusImage = NULL;
	
	this->bonusAppearenceInterval = bonusInterval * 1000;
	this->bonusLastingInterval = lastingProportion * this->bonusAppearenceInterval;
	
	this->grilla = g;
	this->window = w;
	this->fondo = imageFondo;
	this->gameOverImage = new Image("Images/gameOver.bmp");

	this->boardHeight = this->grilla->getAlto() * this->imageHeight;
	this->boardWidth = this->grilla->getAncho() * this->imageWidth;

	int pacman1InitialX = this->imageWidth * 12;
	int pacman1InitialY = this->imageHeight * 18;

	int pacman2InitialX = this->imageWidth * 14;
	int pacman2InitialY = this->imageHeight * 18;

	this->pacman1 = new Pacman("Images/pacman.bmp","Images/pacmanClosed.bmp", this->grilla,
		this->boardHeight, this->boardWidth,
		pacman1InitialX, pacman1InitialY, 3, this->imageHeight, this->imageWidth);
	
	this->pacman2 = new Pacman("Images/pacman2.bmp", "Images/pacman2Closed.bmp", this->grilla,
		this->boardHeight, this->boardWidth,
		pacman2InitialX, pacman2InitialY, 3, this->imageHeight, this->imageWidth);
	
	this->createGhostsForPacman1();
	this->createGhostsForPacman2();

	this->pacman2->changeKeyboardMappings(SDLK_w, SDLK_s, SDLK_a, SDLK_d);
	this->fondoNegro=new Image(this->window->getWidth(),this->window->getHeight());
	
	/**/
	this->window->display(this->fondo, 0, 0, 0, 0, 0, -1);
	SDL_BlitSurface(this->fondo->getSDLSurface(), NULL, this->window->getSDLSurface(), NULL);
	SDL_Flip(this->window->getSDLSurface());

	// 0 means infiinte loop
	this->soundManager->playSound(this->soundManager->getBackgroundPath(), 0);

	this->originalPacmanSpeed=this->pacman1->getPacmanSpeed();

	this->loadSpecialBonus(); //Load all the special Bonus
}

void ScreenManager::createGhostsForPacman1(void)
{
	int ghostInitialX = (this->imageWidth * (this->grilla->getAncho() - 1)) / 2;
	int ghostInitialY = (this->imageHeight * (this->grilla->getAlto() - 1)) / 2;

	this->pacman1Ghosts.add(new Ghost(this->soundManager, "Images/redGhost.bmp", "Images/brownVGhost.bmp" , 
		this->grilla, this->boardHeight, this->boardWidth,
		ghostInitialX - this->imageWidth
		, ghostInitialY - 22, 0, this->pacman1, 
		this->imageHeight, this->imageWidth, false, 0));

	this->pacman1Ghosts.add(new Ghost(this->soundManager, "Images/redGhost.bmp", "Images/brownVGhost.bmp", 
		this->grilla, this->boardHeight, this->boardWidth,
		ghostInitialX + this->imageWidth, ghostInitialY + this->imageHeight, 0, this->pacman1, 
		this->imageHeight, this->imageWidth, true, 1));

	this->pacman1Ghosts.add(new Ghost(this->soundManager, "Images/redGhost.bmp", "Images/brownVGhost.bmp" , 
		this->grilla, this->boardHeight, this->boardWidth,
		ghostInitialX - this->imageWidth, ghostInitialY + this->imageHeight, 0, 
		this->pacman1, this->imageHeight, this->imageWidth, true, 2));

	this->pacman1Ghosts.add(new Ghost(this->soundManager, "Images/redGhost.bmp", "Images/brownVGhost.bmp" , 
		this->grilla, this->boardHeight, this->boardWidth,
		ghostInitialX, 
		ghostInitialY + this->imageHeight, 0, this->pacman1, 
		this->imageHeight, this->imageWidth, true, 3));

}

void ScreenManager::createGhostsForPacman2(void)
{
	int ghostInitialX = (this->imageWidth * (this->grilla->getAncho() - 1)) / 2;
	int ghostInitialY = (this->imageHeight * (this->grilla->getAlto() - 1)) / 2;

	this->pacman2Ghosts.add(new Ghost(this->soundManager,"Images/blueGhost.bmp", "Images/greenVGhost.bmp" , 
		this->grilla, this->boardHeight, this->boardWidth,
		ghostInitialX + this->imageWidth, ghostInitialY -22, 0, this->pacman2, 
		this->imageHeight, this->imageWidth, false, 0));
	
	this->pacman2Ghosts.add(new Ghost(this->soundManager,"Images/blueGhost.bmp","Images/greenVGhost.bmp", 
		this->grilla, this->boardHeight, this->boardWidth,
		ghostInitialX - this->imageWidth, ghostInitialY + this->imageHeight * 2, 0, this->pacman2, 
		this->imageHeight, this->imageWidth, true, 1));

	this->pacman2Ghosts.add(new Ghost(this->soundManager,"Images/blueGhost.bmp", "Images/greenVGhost.bmp", 
		this->grilla, this->boardHeight, this->boardWidth,
		ghostInitialX + this->imageWidth, ghostInitialY + this->imageHeight * 2, 0, 
		this->pacman2, this->imageHeight, this->imageWidth, true, 2));

	this->pacman2Ghosts.add(new Ghost(this->soundManager,"Images/blueGhost.bmp", "Images/greenVGhost.bmp" , 
		this->grilla, this->boardHeight, this->boardWidth,
		ghostInitialX, ghostInitialY + this->imageHeight * 2, 0, this->pacman2, 
		this->imageHeight, this->imageWidth, true, 3));
}

void ScreenManager::handleKeyStroke(void)
{
	if (this->pacman1->isAlive() && this->pacman2->isAlive())
	{
		this->pacman1->handleKeyStroke();
		this->pacman2->handleKeyStroke();
	}
}

void ScreenManager::updateScreen(void)
{
	if (!this->playedOpeningSong)
	{
		this->soundManager->playSound(this->soundManager->getBeginPath(), 1);
		while (this->soundManager->isSoundPlaying(this->soundManager->getBeginPath()))
		{
			// wait until sounds is over playing
		}	
		this->playedOpeningSong = true;
	}

	this->updateBonusEffects(this->pacman1, this->pacman2, this->pacman1Ghosts, this->activeBonusPacman1);
	this->updateBonusEffects(this->pacman1, this->pacman2, this->pacman2Ghosts, this->activeBonusPacman2);
	this->updateSpecialBonus();
	this->updateGhostsVulnerability();
	this->updateGhostsActivation();
	this->deletePacman(this->pacman1);
	this->deletePacman(this->pacman2);
	this->deleteGhosts(this->pacman1Ghosts);
	this->deleteGhosts(this->pacman2Ghosts);
	if (this->pacman1->isAlive() && this->pacman2->isAlive())
	{
		cout<<"pacman1 posx "<<this->pacman1->getX()<<" posy "<<this->pacman1->getY()<<endl;
		cout<<"pacman2 posx "<<this->pacman2->getX()<<" posy "<<this->pacman2->getY()<<endl;
		if (this->isFoodOver())
		{
			// game is finished, someone won
			this->soundManager->pauseSound(this->soundManager->getBackgroundPath());
			this->soundManager->playSound(this->soundManager->getWonPath(), 1);
			while (this->soundManager->isSoundPlaying(this->soundManager->getWonPath()))
			{
				// wait until sounds is over playing
			}
			
			this->finished = true;
		}
		else
		{
			this->handleCollisionWithOppositeCharacters(this->pacman1, this->pacman2, this->pacman2Ghosts);
			this->handleCollisionWithOppositeCharacters(this->pacman2, this->pacman1, this->pacman1Ghosts);
			this->deleteBonus(this->pacman1, this->pacman1Ghosts, true);
			this->deleteBonus(this->pacman2, this->pacman2Ghosts, false);
			this->updatePacman(this->pacman1);
			this->updatePacman(this->pacman2);
			this->updateGhosts(this->pacman1Ghosts);
			this->updateGhosts(this->pacman2Ghosts);
		}
		/*this->deleteBonus(this->pacman1, this->pacman1Ghosts, true);
		this->deleteBonus(this->pacman2, this->pacman2Ghosts, false);*/
	}
	else
	{
		if (this->deadCycles == 0)
		{
			this->soundManager->playSound(this->soundManager->getDiesPath(), 1);
			this->soundManager->pauseSound(this->soundManager->getBackgroundPath());
		}

		if (this->deadCycles < 20)
		{
			// one of the pacmans is dead.
			if (!pacman1->isAlive())
			{
				this->pacman1->rotateWhenDead();
				this->updatePacman(this->pacman1);
			}

			if (!pacman2->isAlive())
			{
				this->pacman2->rotateWhenDead();
				this->updatePacman(this->pacman2);
			}
		}
		else
		{
			int x = (this->window->getWidth() - this->gameOverImage->getWidth()) / 2;
			int y = (this->window->getHeight() - this->gameOverImage->getHeight()) / 2;

			this->window->display(this->gameOverImage, x, y, 0, 0, 0, 20);
		}

		this->deadCycles++;
	}
	SDL_Flip(this->window->getSDLSurface());
}

void ScreenManager::updateGhosts(List<Ghost*>& ghosts)
{
	for (int i = 0; i < ghosts.length(); i++)
	{
		Ghost* g = ghosts[i];
		g->updatePosition();
		int xg = g->getX();
		int yg = g->getY();
		Image* ig = g->getImage();
		this->window->display(ig, xg, yg, 0, 0, 0, 10);
	}
}

void ScreenManager::updatePacman(Pacman* pac)
{
	pac->updatePosition();
	int x = pac->getX();
	int y = pac->getY();
	Image* i = pac->getImage();
	this->window->display(i, x, y, 255, 255, 255, 50);
}

void ScreenManager::updateGhostsVulnerability(void)
{
	if (this->pacman1GhostsVulnerable)
	{
		this->vulnerablePacman1Cycles++;

		if (this->vulnerablePacman1Cycles * this->period >= vulnerableTime)
		{
			for (int i = 0; i < this->pacman1Ghosts.length(); i++)
			{
				this->pacman1Ghosts[i]->setIsVulnerable(false);
			}
		}
	}

	if (this->pacman2GhostsVulnerable)
	{
		this->vulnerablePacman2Cycles++;

		if (this->vulnerablePacman2Cycles * this->period >= vulnerableTime)
		{
			for (int i = 0; i < this->pacman2Ghosts.length(); i++)
			{
				this->pacman2Ghosts[i]->setIsVulnerable(false);
			}
		}
	}
}
void ScreenManager::updateGhostsActivation(void)
{
	this->activationCycles++;
	int milliseconds = this->activationCycles * period;

	if (milliseconds >= this->ghostActivationTime && this->activatedGhosts < this->pacman1Ghosts.length())
	{
		this->activationCycles = 0;
		this->pacman1Ghosts.at(this->activatedGhosts)->setIsActive(true);
		this->pacman2Ghosts.at(this->activatedGhosts)->setIsActive(true);
		this->activatedGhosts++;
	}

}
void ScreenManager::deletePacman(Pacman* pac)
{
	int x = pac->getX();
	int y = pac->getY();
	Image* i = pac->getImage();
	int height = i->getHeight();
	int width = i->getWidth();
	
	this->window->display(this->fondo, x, y, width, height);
}

void ScreenManager::deleteGhosts(List<Ghost*>& ghosts)
{
	for (int i = 0; i < ghosts.length(); i++)
	{
		Ghost* g = ghosts[i];
		int xg = g->getX();
		int yg = g->getY();
		Image* ig = g->getImage();
		int height = ig->getHeight();
		int width = ig->getWidth();
		
		this->window->display(this->fondo, xg, yg, width, height);
	}
}

void ScreenManager::deleteBonus(Pacman *pac, List<Ghost*>& ghosts, bool isPacman1)
{
	ImageArea ia=pac->eatBonus();
	string bonus = pac->getLastEatenBonus();
	if (bonus != "")
	{
		this->handleNormalBonusEating(pac, ghosts, bonus, isPacman1);
	}

	if (this->bonusShowing)
	{
		bool success = pac->tryEatSpecialBonus(this->specialBonusX, this->specialBonusY, 
		this->specialBonusImage->getHeight(), this->specialBonusImage->getWidth());

		if (success)
		{
			this->handleSpecialBonusEating(pac, ghosts, this->bonusToShow.getNombre(), isPacman1);
			this->removeBonusFromMaze();
		}
	}

	this->fondo->display(this->fondoNegro, ia.getX(), ia.getY(), ia.getImageWidth(), ia.getImageHeight());
	this->window->display(this->fondoNegro, ia.getX(), ia.getY(), ia.getImageWidth(), ia.getImageHeight());
}

void ScreenManager::handleCollisionWithOppositeCharacters(Pacman* pac, Pacman* op, 
														  List<Ghost*>& opGhosts)
{
	bool opCollision = false;
	opCollision = CollisionHelper::AreFullyCollisioned(pac->getX(), 
		pac->getY(), op->getX(), op->getY(), 3);

	for (int i = 0; i < opGhosts.length(); i++)
	{
		Ghost* g = opGhosts.at(i);

		opCollision = opCollision || CollisionHelper::AreFullyCollisioned(pac->getX(), 
			pac->getY(), g->getX(), g->getY(), 3);
	}

	if(opCollision)
	{
		this->soundManager->playSound(this->soundManager->getCollisionPath(), 1);
	}
}

bool ScreenManager::isFoodOver()
{
	return (this->pacman1->getEatenBonus() + this->pacman2->getEatenBonus() == this->grilla->getCantidadBonus());
}

bool ScreenManager::gameOver(void)
{
	bool pacmanDead = this->deadCycles >= 40;

	return (pacmanDead || this->finished);
}

Pacman* ScreenManager::getPacman1(void)
{
	return this->pacman1;
}

Pacman* ScreenManager::getPacman2(void)
{
	return this->pacman2;
}

void ScreenManager::handleNormalBonusEating(Pacman* pac, List<Ghost*>& ghosts, string bonus, bool isPacman1)
{
	if (bonus == "alimento")
	{
		// alimento comun
		this->increasePacmanScore(pac, isPacman1, 10, true);
		this->soundManager->playSound(this->soundManager->getEatPath(), 1);

		return;
	}

	if (bonus == "alimentoEspecial")
	{
		this->soundManager->playSound(this->soundManager->getEatPath(), 1);
		
		// alimento bonus, fanstamas vulnerables
		pac->setGhostKills(0);
		this->increasePacmanScore(pac, isPacman1, 50, true);

		for (int i = 0; i < ghosts.length(); i++)
		{
			ghosts[i]->setIsVulnerable(true);
		}

		if (isPacman1)
		{
			this->pacman1GhostsVulnerable = true;
			vulnerablePacman1Cycles = 0;
		}
		else
		{
			this->pacman2GhostsVulnerable = true;
			vulnerablePacman2Cycles = 0;
		}
		return;
	}
}

void ScreenManager::handleSpecialBonusEating(Pacman* pac, List<Ghost*>& ghosts, std::string bonus, bool isPacman1)
{
	this->soundManager->playSound(this->soundManager->getBonusPath(), 1);

	if (bonus == "alimentoDuplicador" && this->bonusShowing)
	{
		// alimento duplicador
		pac->setScoreMultiplier(2);
		
		if (isPacman1)
		{
			this->activeBonusPacman1["alimentoDuplicador"] = 
				this->bonusToShow.getDuracionTiempo(this->period);
		}
		else
		{
			this->activeBonusPacman2["alimentoDuplicador"] = 
				this->bonusToShow.getDuracionTiempo(this->period);
		}
		return;
	}

	if (bonus == "anana" && this->bonusShowing)
	{
		// bonus anana
		this->increasePacmanScore(pac, isPacman1, 100, false);
		return;
	}

	if (bonus == "manzana" && this->bonusShowing)
	{
		// alimento manzana
		this->increasePacmanScore(pac, isPacman1, 200, false);
		return;
	}

	if (bonus == "alimentoCongelado" && this->bonusShowing)
	{
		if (isPacman1)
		{
			this->activeBonusPacman1["alimentoCongelado"] = 
				this->bonusToShow.getDuracionTiempo(this->period);
			this->pacman2->inmovilizar(true);
		}
		else
		{
			this->activeBonusPacman2["alimentoCongelado"] = 
				this->bonusToShow.getDuracionTiempo(this->period);
			this->pacman1->inmovilizar(true);
		}

		return;
	}
		
	if (bonus == "alimentoRobaPuntos" && this->bonusShowing)
	{
		if (isPacman1)
		{
			this->activeBonusPacman1["alimentoRobaPuntos"] = 
				this->bonusToShow.getDuracionTiempo(this->period);
		}
		else
		{
			this->activeBonusPacman2["alimentoRobaPuntos"] = 
				this->bonusToShow.getDuracionTiempo(this->period);
		}
		return;
	}

	if (bonus == "alimentoDuplicaVelocidad" && this->bonusShowing)
	{
		if (isPacman1)
		{
			this->pacman1->setPacmanSpeed(this->pacman1->getPacmanSpeed()*2); 
			this->activeBonusPacman1["alimentoDuplicaVelocidad"] = 
				this->bonusToShow.getDuracionTiempo(this->period);
		}
		else
		{
			this->pacman2->setPacmanSpeed(this->pacman2->getPacmanSpeed()*2); 
			this->activeBonusPacman2["alimentoDuplicaVelocidad"] = 
				this->bonusToShow.getDuracionTiempo(this->period);
		}
		
		return;
	}

	if (bonus == "alimentoReduceVelocidad" && this->bonusShowing)
	{
		if (isPacman1)
		{
			this->pacman2->setPacmanSpeed(this->pacman2->getPacmanSpeed()/2); 
			this->activeBonusPacman1["alimentoReduceVelocidad"] = 
				this->bonusToShow.getDuracionTiempo(this->period);
		}
		else
		{
			this->pacman1->setPacmanSpeed(this->pacman1->getPacmanSpeed()/2); 
			this->activeBonusPacman2["alimentoReduceVelocidad"] = 
				this->bonusToShow.getDuracionTiempo(this->period);
		}

		return;
	}

	if (bonus == "alimentoPersecucion" && this->bonusShowing)
	{
		if (isPacman1)
		{
			this->activeBonusPacman1["alimentoPersecucion"] = 
				this->bonusToShow.getDuracionTiempo(this->period);
			this->assignPacmanToGhosts(this->pacman1Ghosts, this->pacman2);
		}
		else
		{
			this->assignPacmanToGhosts(this->pacman2Ghosts, this->pacman1);
			this->activeBonusPacman2["alimentoPersecucion"] = 
				this->bonusToShow.getDuracionTiempo(this->period);
		}

		return;
	}
}
void ScreenManager::assignPacmanToGhosts(List<Ghost*>& ghosts, Pacman* pac)
{
	for (int i = 0; i < ghosts.length(); i++)
	{
		Ghost* g = ghosts.at(i);
		g->setPacman(pac);
	}
}
void ScreenManager::loadSpecialBonus(void){
	
	List<TipoBonus> specialBonus(this->grilla->getTiposBonus());
	int lenght=specialBonus.length();
	for (int i=0; i < lenght ; i++)
	{
		this->sbm.addBonusType(specialBonus.at(i));
		this->activeBonusPacman1[specialBonus.at(i).getNombre()]=0;
		this->activeBonusPacman2[specialBonus.at(i).getNombre()]=0;
	}

}

void ScreenManager::updateSpecialBonus(void)
{
	this->bonusAppearenceCycles++;
	int timeSinceAppearence = this->bonusAppearenceCycles * this->period;

	if (timeSinceAppearence >= this->bonusAppearenceInterval)
	{
		// bonus should appear
		this->bonusAppearenceCycles = 0;

		this->sbm.selectBonus();
		
		if (this->sbm.isSelectedBonusValid())
		{
			this->bonusToShow=this->sbm.getSelectedBonus();
			this->bonusShowing =true;
			cout<<"Bono "<<bonusToShow.getNombre()<<"	activo"<<endl;
			this->placeBonusInMaze(this->bonusToShow);
			this->bonusShowing =true;
		}
	}

	timeSinceAppearence = this->bonusAppearenceCycles * this->period;

	if (this->bonusShowing && timeSinceAppearence >= this->bonusLastingInterval)
	{

		// remove bonus from maze
		this->removeBonusFromMaze();
		cout<<"Bono "<<this->bonusToShow.getNombre()<<"	termino Activacion"<<endl;
	}
}

void ScreenManager::updateBonusEffects(Pacman* pac, Pacman* op, List<Ghost*>& ghosts, map<string, int>& activeBonusForPacman)
{
	std::map<std::string, int>::iterator bonusTimeEffect;

	for (bonusTimeEffect = activeBonusForPacman.begin(); 
		bonusTimeEffect != activeBonusForPacman.end();
		bonusTimeEffect++) 
	{
		if (bonusTimeEffect->second > 0)
		{
			int remainingTime = bonusTimeEffect->second - this->period;

			if (remainingTime <= 0)
			{
				bonusTimeEffect->second = 0;
				//cancel bonus effect
				this->cancelBonusEffect(bonusTimeEffect->first, pac, op, ghosts);
			}
			else
			{
				bonusTimeEffect->second = remainingTime;
			}
		}
	}
}
void ScreenManager::cancelBonusEffect(string bonusType, Pacman* pac, Pacman* op, List<Ghost*>& ghosts)
{
	if (bonusType == "alimentoCongelado")
	{
		op->inmovilizar(false);
		return;
	}
	
	if (bonusType == "alimentoDuplicaVelocidad")
	{
		pac->setPacmanSpeed(this->originalPacmanSpeed);
		return;
	} 

	if (bonusType == "alimentoReduceVelocidad")
	{
		op->setPacmanSpeed(this->originalPacmanSpeed);
		return;
	}

	if (bonusType == "alimentoPersecucion")
	{
		this->assignPacmanToGhosts(ghosts, pac);
		return;
	}

	if (bonusType == "alimentoDuplicador")
	{
		pac->setScoreMultiplier(1);
		return;
	}

}
void ScreenManager::increasePacmanScore(Pacman* pac, bool isPacman1, int score, bool increaseCount)
{
	if (this->activeBonusPacman1["alimentoRobaPuntos"] > 0	&& !isPacman1)
	{
		this->pacman1->increaseScore(score);
		if (increaseCount)
		{
			this->pacman1->increaseEatenBonus();
		}
	}
	else if (this->activeBonusPacman2["alimentoRobaPuntos"] > 0	&& isPacman1)
	{
		this->pacman2->increaseScore(score);
		if (increaseCount)
		{
			this->pacman2->increaseEatenBonus();
		}
	}
	else
	{
		pac->increaseScore(score);
		if (increaseCount)
		{
			pac->increaseEatenBonus();
		}
	}
}

void ScreenManager::placeBonusInMaze(TipoBonus& bonus)
{
	//Acá hay que lograr insertar la imagen
	Textura& t = bonus.getTextura();
	string imagePath = t.getPath();
	this->specialBonusImage = new Image(imagePath);

	int height = this->specialBonusImage->getHeight();

	if (this->specialBonusImage->getHeight() > this->imageHeight)
	{
		height = this->imageHeight;	
	}

	int width = this->specialBonusImage->getHeight();

	if (this->specialBonusImage->getWidth() > this->imageWidth)
	{
		width = this->imageWidth;	
	}

	this->setMinimalDistanceForBonuses(this->pacman1->getX(), this->pacman1->getY(), 
									   this->pacman2->getX(), this->pacman2->getY());
	/*this->specialBonusX = this->imageWidth * 12;
	this->specialBonusY = this->imageHeight * 18;*/

	this->specialBonusImage->resize(width, height);

	/*this->fondo->display(this->specialBonusImage, this->specialBonusX,
		this->specialBonusY, t.getRed(), t.getGreen(), t.getBlue(), t.getDelta());*/

	this->window->display(this->specialBonusImage, this->specialBonusX,
		this->specialBonusY, t.getRed(), t.getGreen(), t.getBlue(), t.getDelta());
}

void ScreenManager::removeBonusFromMaze(void)
{
	// bonus should dissapear
	this->bonusShowing=false;

	/*this->fondo->display(this->fondoNegro, this->specialBonusX, this->specialBonusY,
		this->specialBonusImage->getWidth(), this->specialBonusImage->getHeight());*/

	this->window->display(this->fondo, this->specialBonusX, this->specialBonusY,
		this->specialBonusImage->getWidth(), this->specialBonusImage->getHeight());

	delete this->specialBonusImage;

	this->specialBonusImage = NULL;
}

ScreenManager::~ScreenManager(void)
{
	delete this->pacman1;
	delete this->pacman2;
	delete this->gameOverImage;
	delete this->fondoNegro;
	delete this->soundManager;

	if (this->specialBonusImage != NULL)
	{
		delete this->specialBonusImage;
	}

	for (int i = 0; i < this->pacman1Ghosts.length(); i++)
	{
		delete this->pacman1Ghosts.getValueAt(i);
	}

	for (int i = 0; i < this->pacman2Ghosts.length(); i++)
	{
		delete this->pacman2Ghosts.getValueAt(i);
	}
}
void ScreenManager::setMinimalDistanceForBonuses(int xPac1, int yPac1, int xPac2, int yPac2){

	int middleX=abs(xPac1-xPac2)/2.0;
	int middleY=abs(yPac1-yPac2)/2.0;
	int cont=0;

	if (xPac1 < xPac2)
		middleX=xPac1+middleX;
	else
		middleX=xPac2+middleX;

	if (yPac1 < yPac2)
		middleY=yPac1+middleY;
	else
		middleY=yPac2+middleY;

	this->normalizeXY(middleX,middleY, 16);

	/*while (!isPointInRoad(middleX,middleY)){
		middleX++;
		middleY++;
		middleX%=426;
		middleY%=426;

	}*/
	this->normalizeXY(middleX,middleY, 30);
	this->specialBonusX=middleX;
	this->specialBonusY=middleY;

}

bool ScreenManager::isPointInRoad(int middleX, int middleY){

	int width = this->specialBonusImage->getWidth();
	int height = this->specialBonusImage->getHeight();

	int x1 = middleX / this->imageWidth;
	int y1 = middleY / this->imageHeight;
	
	int x2 = (middleX + width) / this->imageWidth;
	int y2 = (middleY + height) / this->imageHeight;

	if (x1 < 0 || x2 >= this->grilla->getAncho() || y1 < 0 || y2 >= this->grilla->getAlto())
	{
		return false;
	}

	Celda* c1 = this->grilla->getCelda(y1, x1);
	Camino* cam1 = dynamic_cast<Camino*>(c1);
	if (cam1 == NULL || CollisionHelper::IsPointInRectangle(middleX,middleY,155,218,286,286)){
		return false;
	}

	return true;

}

void ScreenManager::normalizeXY(int &x, int &y, int delta){

	int poscionesX[8]={18,34,102,204,240,291,342,426};
	int posicionesY[7]={18,87,138,204,306,375,444};

	for (int i=0; i< 8; i++){
		if (abs(x- poscionesX[i]) < delta){
			x=poscionesX[i];
			break;
		}
	}

	for (int i=0; i< 7; i++){
		if (abs(y- posicionesY[i]) < delta){
			y=posicionesY[i];
			break;
		}
	}
}
