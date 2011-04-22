#include "sdl/sdl.h"

#pragma once

class Window
{
public:
	Window(void);
	//Window(Image fondo);
	SDL_Surface* getSDL_Surface();
	~Window(void);
private:
	SDL_Surface* surface;
};
