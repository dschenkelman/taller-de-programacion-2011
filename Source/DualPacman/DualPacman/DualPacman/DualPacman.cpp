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

//using namespace std;

#define SDL_main main 

int main(int argc, char* argv[])
{
	int width = 640;
	int height = 480;
	Window* w = new Window("::Dual Pacman::", height, width);
	
	// Actividad de Inicio
	PresentationActivity* pActivity = new PresentationActivity(width, height);
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