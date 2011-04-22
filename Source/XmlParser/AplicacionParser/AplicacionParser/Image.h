#pragma once
#include <string>
#include "SDL.h"

class Image
{
	SDL_Surface* image;
	int height;
	int width;
public:
	Image(std::string& path);
	~Image(void);
	SDL_Surface* getSDLSurface(void);
	int getWidth(void);
	int getHeight(void);
};
