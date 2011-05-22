#include "StdAfx.h"
#include "ScreenManager.h"
#include "Pacman.h"
#include "Window.h"
#include <string>

using namespace std;

ScreenManager::ScreenManager(Window* w, string pathFondo)
{
	this->window = w;
	this->fondo = new Image(pathFondo);
	this->pacman1 = new Pacman("Images/pacman.bmp", 
		this->window->getHeight(), this->window->getWidth(),
		0, 0);

	this->pacman2 = new Pacman("Images/pacman2.bmp", 
		this->window->getHeight(), this->window->getWidth(),
		this->window->getWidth() - (this->pacman1->getImage()->getWidth() + 1), 0);

	this->pacman1Ghosts.add(new Ghost("Images/redGhost.bmp", this->window->getHeight(), this->window->getWidth(),
		0, this->window->getHeight() - (30 + 1), this->pacman1));

	this->pacman2Ghosts.add(new Ghost("Images/blueGhost.bmp", this->window->getHeight(), this->window->getWidth(),
		0, this->window->getHeight() - (30 + 1), this->pacman2));

	this->pacman2->changeKeyboardMappings(SDLK_w, SDLK_s, SDLK_a, SDLK_d);
}

void ScreenManager::handleKeyStroke(void)
{
	this->pacman1->handleKeyStroke();
	this->pacman2->handleKeyStroke();
}

void ScreenManager::updateScreen(void)
{
	this->window->display(this->fondo, 0, 0, 0, 0, 0, -1);
	this->updatePacman(this->pacman1);
	this->updatePacman(this->pacman2);
	this->updateGhosts(this->pacman1Ghosts);
	this->updateGhosts(this->pacman2Ghosts);
	this->window->refresh();
}

void ScreenManager::updateGhosts(List<Ghost*> ghosts)
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
	this->window->display(i, x, y, 255, 255, 255, 10);
}

ScreenManager::~ScreenManager(void)
{
	delete this->fondo;
	delete this->pacman1;
	delete this->pacman2;

	for (int i = 0; i < this->pacman1Ghosts.length(); i++)
	{
		delete this->pacman1Ghosts.getValueAt(i);
	}

	for (int i = 0; i < this->pacman2Ghosts.length(); i++)
	{
		delete this->pacman2Ghosts.getValueAt(i);
	}
}