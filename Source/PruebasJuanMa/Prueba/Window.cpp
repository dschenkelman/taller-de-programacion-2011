#include "StdAfx.h"
#include "Window.h"
#include "Image.h"

Window::Window(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
	}
	atexit(SDL_Quit);

	this->surface = SDL_SetVideoMode(640, 480, 24, SDL_DOUBLEBUF);
	if (this->surface == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
	}
}

SDL_Surface* Window::getSDL_Surface()
{
	return this->surface;
}

Window::~Window()
{
	SDL_FreeSurface(this->surface);
}
