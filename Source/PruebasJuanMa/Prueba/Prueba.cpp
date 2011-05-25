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

	// banner: dual
	Image* dualBanner = new Image("images/dual.bmp");
	SDL_Rect* recDualBanner = new SDL_Rect();
	recDualBanner->h = dualBanner->getHeight();
	recDualBanner->w = dualBanner->getWidth();
	recDualBanner->x = 150;
	recDualBanner->y = 5;
	SDL_BlitSurface(dualBanner->getSDLSurface(), NULL, screen, recDualBanner);
	
	RichText* text0 = new RichText("pacman", RichText::NORMAL);	
	SDL_Rect* recText0 = new SDL_Rect();
	recText0->h = text0->getImage()->getHeight();
	recText0->w = text0->getImage()->getWidth();
	recText0->x = 250;
	recText0->y = 110;
	SDL_BlitSurface(text0->getImage()->getSDLSurface(), NULL, screen, recText0);

	// menu header
	RichText* menuHeader = new RichText("Menu", RichText::NORMAL);	
	SDL_Rect* recMenuHeader = new SDL_Rect();
	recMenuHeader->h = menuHeader->getImage()->getHeight();
	recMenuHeader->w = menuHeader->getImage()->getWidth();
	recMenuHeader->x = 250;
	recMenuHeader->y = 200;
	SDL_BlitSurface(menuHeader->getImage()->getSDLSurface(), NULL, screen, recMenuHeader);

	// menu item start
	RichText* menuStart = new RichText("START", RichText::NORMAL);	
	SDL_Rect* recMenuStart = new SDL_Rect();
	recMenuStart->h = menuStart->getImage()->getHeight();
	recMenuStart->w = menuStart->getImage()->getWidth();
	recMenuStart->x = 250;
	recMenuStart->y = 250;
	SDL_BlitSurface(menuStart->getImage()->getSDLSurface(), NULL, screen, recMenuStart);

	// menu item quit
	RichText* menuQuit = new RichText("QUIT", RichText:: NORMAL);	
	SDL_Rect* recMenuQuit = new SDL_Rect();
	recMenuQuit->h = menuQuit->getImage()->getHeight();
	recMenuQuit->w = menuQuit->getImage()->getWidth();
	recMenuQuit->x = 250;
	recMenuQuit->y = 300;
	SDL_BlitSurface(menuQuit->getImage()->getSDLSurface(), NULL, screen, recMenuQuit);

	// creo la flechita
	Image* flechita = new Image("images/menu-arrow.bmp");
	SDL_Rect* recFlechita = new SDL_Rect();
	recFlechita->h = flechita->getHeight();
	recFlechita->w = flechita->getWidth();
	recFlechita->x = 200;
	recFlechita->y = 250;
	SDL_BlitSurface(flechita->getSDLSurface(), NULL, screen, recFlechita);
	
	SDL_Flip(screen);

	// flechita de menu
	SDL_Event e;
	bool running = true;
 	bool keyup = false;
	bool keydown = false;

	while(running) 
	{
		while(SDL_PollEvent(&e)) 
		{
			switch(e.type)
			{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym){
					  case SDLK_UP:
						if(keydown){
							for(int posY=0; posY<5; posY++){
								SDL_FillRect(screen, recFlechita, 0);
								recFlechita->y = 265-(5*posY);
								SDL_BlitSurface(flechita->getSDLSurface(), NULL, screen, recFlechita);
								SDL_Flip(screen);
								SDL_Delay(30);
							}
						}
						keyup = true;
						keydown = false;
						break;
					  case SDLK_DOWN:
						if(keyup){
							for(int posY=0; posY<5; posY++){
								SDL_FillRect(screen, recFlechita, 0);
								recFlechita->y = 265+(5*posY);
								SDL_BlitSurface(flechita->getSDLSurface(), NULL, screen, recFlechita);
								SDL_Flip(screen);
								SDL_Delay(30);
							}
						}
						keydown = true;
						keyup = false;
						break;
					}

					break;
			}
		}
	}

	
	
	// libero memoria
	//free(text1);
	 
	return 0;
}
