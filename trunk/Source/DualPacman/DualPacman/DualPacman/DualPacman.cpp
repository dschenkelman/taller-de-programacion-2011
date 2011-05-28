// DualPacman.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include "Window.h"
#include "sdl/SDL.h"
#include "ScreenManager.h"
#include "MenuActivity.h"
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace System;

#define SDL_main main 



int main(int argc, char* argv[])
{
	Window* w = new Window("::Dual Pacman::", 480, 640);
	
	// Actividad de Inicio
	MenuActivity* menuActivity = new MenuActivity();
	menuActivity->init();
	
	// Seteo la actividad
	w->setCurrentActivity(menuActivity);
	
	menuActivity->drawViews();

	// Actualizo la ventana
	w->refresh();
	
	// Inicio manejo de eventos
	w->init();
	
	return 0;
}