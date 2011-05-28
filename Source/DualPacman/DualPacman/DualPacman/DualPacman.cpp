// DualPacman.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include "Window.h"
#include "sdl/SDL.h"
#include "ScreenManager.h"
#include "PresentationActivity.h"
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
	PresentationActivity* pActivity = new PresentationActivity();
	pActivity->init();
	
	// Seteo la actividad
	w->setCurrentActivity(pActivity);
	
	pActivity->drawViews();

	// Actualizo la ventana
	w->refresh();
	
	// Inicio manejo de eventos
	w->init();
	
	return 0;
}