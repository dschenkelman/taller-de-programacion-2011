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
	this->pacman1 = new Pacman("Images/pacman.bmp", this->window->getHeight(), this->window->getWidth());
}

void ScreenManager::handleKeyStroke(void)
{
	this->pacman1->handleKeyStroke();
}

void ScreenManager::updateScreen(void)
{
	this->pacman1->updatePosition();
	int x = this->pacman1->getX();
	int y = this->pacman1->getY();
	Image* i = this->pacman1->getImage();
	this->window->display(this->fondo, 0, 0, 0, 0, 0, -1);
	this->window->display(i, x, y, 255, 255, 255, 10);
	this->window->refresh();
}

ScreenManager::~ScreenManager(void)
{
	delete this->fondo;
	delete this->pacman1;
}