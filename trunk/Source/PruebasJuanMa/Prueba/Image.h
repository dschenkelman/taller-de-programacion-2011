#include "sdl/sdl.h"
#include "string.h"

#pragma once

class Image
{
public:
	Image(void);
	Image(String uri);
	//Image(String uri, int x, int y, int width, int height);
	~Image(void);
private:
	SDL_Surface* surface;
};
