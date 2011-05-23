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

	RichText* text0 = new RichText("CABA", RichText::MENU_HEADER1);	
	SDL_Rect* recText0 = new SDL_Rect();
	recText0->h = text0->getImage()->getHeight();
	recText0->w = text0->getImage()->getWidth();
	recText0->x = 100;
	recText0->y = 50;

	RichText* text1 = new RichText("ABA", RichText::MENU_HEADER2);	
	SDL_Rect* recText1 = new SDL_Rect();
	recText1->h = text1->getImage()->getHeight();
	recText1->w = text1->getImage()->getWidth();
	recText1->x = 100;
	recText1->y = 150;

	RichText* text2 = new RichText("BAA", RichText::MENU_ITEM);	
	SDL_Rect* recText2 = new SDL_Rect();
	recText2->h = text2->getImage()->getHeight();
	recText2->w = text2->getImage()->getWidth();
	recText2->x = 100;
	recText2->y = 200;
	
	// Pego la imagen en la pantalla
	SDL_BlitSurface(text0->getImage()->getSDLSurface(), NULL, screen, recText0);
	SDL_BlitSurface(text1->getImage()->getSDLSurface(), NULL, screen, recText1);
	SDL_BlitSurface(text2->getImage()->getSDLSurface(), NULL, screen, recText2);
	SDL_Flip(screen);

	SDL_Delay(5000);
	
	// libero memoria
	free(text1);
	 
	return 0;
}
