#include "sdl/sdl.h"
#include "Window.h"

#pragma once

class Image
{
public:
	//Image(void);
	Image(char* uri);
	//Image(String uri, int x, int y, int width, int height);
	void paste(SDL_Surface* board, int x, int y);
	void paste(Window board, int x, int y);
	~Image(void);
private:
	SDL_Surface* surface;
};
