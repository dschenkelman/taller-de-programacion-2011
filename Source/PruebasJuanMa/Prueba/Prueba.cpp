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

	SDL_Delay(1000);
	
	/** Agrandar imagen */

	// nueva imagen
	Image* imgSmile = new Image("uva.bmp");
	
	int origW = imgSmile->getWidth();
	int origH = imgSmile->getHeight();
	
	// Rotacion
	Uint32 pixelAlpha = SDL_MapRGB(imgSmile->getFormat(), 255, 0, 0);
	imgSmile->rotate(45, pixelAlpha);

	imgSmile->resize(100, 40);
	
	// Pego la imagen en la pantalla
	SDL_BlitSurface(imgSmile->getSDLSurface(), NULL, screen, NULL);
	SDL_Flip(screen);

	SDL_Delay(7000);
	
	// libero memoria
	free(imgSmile);
	 
	return 0;
}
