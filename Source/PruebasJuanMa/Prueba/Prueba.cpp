// Prueba.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include <stdio.h>
#include <string> 
#include <iostream> 
#include <sstream>
#include "XMLParser.h"
#include "Obstaculo.h"
#include "Celda.h"
#include "Camino.h"
#include "Mapa.h"
#include "ScreenLogger.h"
#include <math.h>
#include "sdl/sdl.h"
#include "resampler.h"
#include "Window.h"
#include "Image.h"
#include "Rotador.h"
#include "RichTextView.h"
#include "MenuActivity.h"

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
