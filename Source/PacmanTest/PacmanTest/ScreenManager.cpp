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
		0, this->window->getHeight() - (this->pacman1->getImage()->getHeight() + 1));

	this->pacman2->changeKeyboardMappings(SDLK_w, SDLK_s, SDLK_a, SDLK_d);
}

void ScreenManager::handleKeyStroke(void)
{
	this->pacman1->handleKeyStroke();
	this->pacman2->handleKeyStroke();
}

void ScreenManager::updateScreen(void)
{
	this->pacman1->updatePosition();
	this->pacman2->updatePosition();
	int x1 = this->pacman1->getX();
	int y1 = this->pacman1->getY();
	int x2 = this->pacman2->getX();
	int y2 = this->pacman2->getY();
	Image* i1 = this->pacman1->getImage();
	Image* i2 = this->pacman2->getImage();
	this->window->display(this->fondo, 0, 0, 0, 0, 0, -1);
	this->window->display(i1, x1, y1, 255, 255, 255, 10);
	this->window->display(i2, x2, y2, 255, 255, 255, 10);
	this->window->refresh();
}

ScreenManager::~ScreenManager(void)
{
	delete this->fondo;
	delete this->pacman1;
}