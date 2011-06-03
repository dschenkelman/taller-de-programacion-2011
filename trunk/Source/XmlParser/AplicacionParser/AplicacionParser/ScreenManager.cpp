#include "StdAfx.h"
#include "ScreenManager.h"
#include "Pacman.h"
#include "Window.h"
#include "ImageArea.h"
#include <string>

using namespace std;

ScreenManager::ScreenManager(Activity* w, Image* imageFondo, Grilla* g, int imageHeight, int imageWidth, Uint32 period) 
: deadCycles(0), imageHeight(imageHeight), imageWidth(imageWidth), period(period),
vulnerablePacman1Cycles(0), vulnerablePacman2Cycles(0), 
pacman1GhostsVulnerable(false), pacman2GhostsVulnerable(false)
{
	this->grilla = g;
	this->window = w;
	this->fondo = imageFondo;
	this->gameOverImage = new Image("Images/gameOver.bmp");

	int pacman1InitialX = this->imageWidth * 11;
	int pacman1InitialY = this->imageHeight * 18;

	int pacman2InitialX = this->imageWidth * 13;
	int pacman2InitialY = this->imageHeight * 18;

	this->pacman1 = new Pacman("Images/pacman.bmp","Images/pacmanClosed.bmp", this->grilla,
		this->window->getHeight(), this->window->getWidth(),
		pacman1InitialX, pacman1InitialY, 3, this->imageHeight, this->imageWidth);

	this->pacman2 = new Pacman("Images/pacman2.bmp", "Images/pacman2Closed.bmp", this->grilla,
		this->window->getHeight(), this->window->getWidth(),
		pacman2InitialX, pacman2InitialY, 3, this->imageHeight, this->imageWidth);

	this->createGhostsForPacman1();
	this->createGhostsForPacman2();

	this->pacman2->changeKeyboardMappings(SDLK_w, SDLK_s, SDLK_a, SDLK_d);
	this->fondoNegro=new Image(this->window->getWidth(),this->window->getHeight());
	
	/**/
	this->window->display(this->fondo, 0, 0, 0, 0, 0, -1);
	SDL_BlitSurface(this->fondo->getSDLSurface(), NULL, this->window->getSDLSurface(), NULL);
	SDL_Flip(this->window->getSDLSurface());
}

void ScreenManager::createGhostsForPacman1(void)
{
	int ghostInitialX = (this->imageWidth * (this->grilla->getAncho() - 1)) / 2;
	int ghostInitialY = (this->imageHeight * (this->grilla->getAlto() - 1)) / 2;
	
	this->pacman1Ghosts.add(new Ghost("Images/redGhost.bmp", "Images/brownVGhost.bmp", 
		this->grilla, this->window->getHeight(), this->window->getWidth(),
		ghostInitialX + 30, ghostInitialY + 20, 2, this->pacman1, 
		this->imageHeight, this->imageWidth));

	this->pacman1Ghosts.add(new Ghost("Images/redGhost.bmp", "Images/brownVGhost.bmp" , 
		this->grilla, this->window->getHeight(), this->window->getWidth(),
		ghostInitialX - 30, ghostInitialY + 20, 2, 
		this->pacman1, this->imageHeight, this->imageWidth));

	this->pacman1Ghosts.add(new Ghost("Images/redGhost.bmp", "Images/brownVGhost.bmp" , 
		this->grilla, this->window->getHeight(), this->window->getWidth(),
		ghostInitialX, 
		ghostInitialY - 20, 2, this->pacman1, 
		this->imageHeight, this->imageWidth));

	this->pacman1Ghosts.add(new Ghost("Images/redGhost.bmp", "Images/brownVGhost.bmp" , 
		this->grilla, this->window->getHeight(), this->window->getWidth(),
		ghostInitialX, 
		ghostInitialY - 20, 2, this->pacman1, 
		this->imageHeight, this->imageWidth));
}

void ScreenManager::createGhostsForPacman2(void)
{
	int ghostInitialX = (this->imageWidth * (this->grilla->getAncho() - 1)) / 2;
	int ghostInitialY = (this->imageHeight * (this->grilla->getAlto() - 1)) / 2;

	this->pacman2Ghosts.add(new Ghost("Images/blueGhost.bmp","Images/greenVGhost.bmp", 
		this->grilla, this->window->getHeight(), this->window->getWidth(),
		ghostInitialX - 30, ghostInitialY + 20, 2, this->pacman2, 
		this->imageHeight, this->imageWidth));

	this->pacman2Ghosts.add(new Ghost("Images/blueGhost.bmp", "Images/greenVGhost.bmp", 
		this->grilla, this->window->getHeight(), this->window->getWidth(),
		ghostInitialX + 30, ghostInitialY + 20, 2, 
		this->pacman2, this->imageHeight, this->imageWidth));

	this->pacman2Ghosts.add(new Ghost("Images/blueGhost.bmp", "Images/greenVGhost.bmp" , 
		this->grilla, this->window->getHeight(), this->window->getWidth(),
		ghostInitialX, ghostInitialY - 20, 2, this->pacman2, 
		this->imageHeight, this->imageWidth));

	this->pacman2Ghosts.add(new Ghost("Images/blueGhost.bmp", "Images/greenVGhost.bmp" , 
		this->grilla, this->window->getHeight(), this->window->getWidth(),
		ghostInitialX, ghostInitialY - 20, 2, this->pacman2, 
		this->imageHeight, this->imageWidth));
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
	this->updateGhostsVulnerability();
	this->deletePacman(this->pacman1);
	this->deletePacman(this->pacman2);
	this->deleteGhosts(this->pacman1Ghosts);
	this->deleteGhosts(this->pacman2Ghosts);
	if (this->pacman1->isAlive() && this->pacman2->isAlive())
	{
		this->updatePacman(this->pacman1);
		this->updatePacman(this->pacman2);
		this->updateGhosts(this->pacman1Ghosts);
		this->updateGhosts(this->pacman2Ghosts);
		this->deleteBonus(this->pacman1, this->pacman1Ghosts, true);
		this->deleteBonus(this->pacman2, this->pacman2Ghosts, false);
	}
	else
	{
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
void ScreenManager::deletePacman(Pacman* pac)
{
	int x = pac->getX();
	int y = pac->getY();
	Image* i = pac->getImage();
	int height = i->getHeight();
	int width = i->getWidth();
	
	this->window->display(this->fondoNegro, x, y, width, height);
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
		
		this->window->display(this->fondoNegro, xg, yg, width, height);
	}
}

void ScreenManager::deleteBonus(Pacman *pac, List<Ghost*>& ghosts, bool isPacman1)
{
	ImageArea ia=pac->eatBonus();
	string bonus = pac->getLastEatenBonus();
	if (bonus != "")
	{
		this->handleBonusEating(pac, ghosts, bonus, isPacman1);
	}

	/*this->fondo->display(this->fondoNegro, ia.getX(), ia.getY(), ia.getImageWidth(), ia.getImageHeight());*/
}
void ScreenManager::startGame(void)
{
	////esperar para cerrar
	//SDL_Event e;
	//bool running = true;
	//this->period = 1000.0 / 120;
 //
	//this->window->display(this->fondo, 0, 0, 0, 0, 0, -1);
	//while(!this->gameOver()) 
	//{
	//	SDL_Delay(this->period);
	//	this->updateScreen();
	//	while(SDL_PollEvent(&e)) 
	//	{
	//		switch(e.type)
	//		{
	//			case SDL_QUIT:
	//				running = false;
	//				//this->window->close();
	//				return;
	//			default:
	//				this->handleKeyStroke();
	//		}
	//	}
	//}
}

bool ScreenManager::gameOver(void)
{
	// eventually this will also include whether all bonuses have been eaten
	return (this->deadCycles >= 40 || (this->pacman1->getEatenBonus() + this->pacman2->getEatenBonus() == this->grilla->getCantidadBonus())) ;
}
void ScreenManager::handleBonusEating(Pacman* pac, List<Ghost*>& ghosts, string bonus, bool isPacman1)
{
	if (bonus == "alimento")
	{
		// alimento comun
		pac->increaseScore(10);
		pac->increaseEatenBonus();
		return;
	}

	if (bonus == "alimentoEspecial")
	{
		// alimento bonus, fanstamas vulnerablesppp
		pac->setGhostKills(0);
		pac->increaseScore(50);
		pac->increaseEatenBonus();
		for (int i = 0; i < ghosts.length(); i++)
		{
			ghosts[i]->setIsVulnerable(true);
		}

		if (isPacman1)
		{
			this->pacman1GhostsVulnerable = true;
		}
		else
		{
			this->pacman2GhostsVulnerable = true;
		}

		return;
	}
}
ScreenManager::~ScreenManager(void)
{
	delete this->pacman1;
	delete this->pacman2;
	delete this->gameOverImage;
	delete this->fondoNegro;

	for (int i = 0; i < this->pacman1Ghosts.length(); i++)
	{
		delete this->pacman1Ghosts.getValueAt(i);
	}

	for (int i = 0; i < this->pacman2Ghosts.length(); i++)
	{
		delete this->pacman2Ghosts.getValueAt(i);
	}
}
