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
#include "RichText.h"
#include "MenuActivity.h"

#define SDL_main main 


int main(int argc, char* argv[])
{
	//Window ventana = Window();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);

	SDL_Surface *screen;
	 
	screen = SDL_SetVideoMode(640, 480, 24, SDL_DOUBLEBUF);
	if (screen == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}

	// banner: dual
	Image* dualBanner = new Image("images/dual.bmp");
	
	MenuActivity* menuActivity = new MenuActivity();
	menuActivity->init();
	
	SDL_BlitSurface(menuActivity->getSDLSurface(), NULL, screen, NULL);
	SDL_Flip(screen);

	SDL_Event e;
	bool running = true;
	while(running) 
	{
		while(SDL_PollEvent(&e)) 
		{
			switch(e.type)
			{
				case SDL_QUIT:
					running = false;
					break;
				default:
					menuActivity->notify(e);
					SDL_BlitSurface(menuActivity->getSDLSurface(), NULL, screen, NULL);
					SDL_Flip(screen);
					break;
			}
		}
	}


	// libero memoria
	//free(text1);
	 
	return 0;
}
