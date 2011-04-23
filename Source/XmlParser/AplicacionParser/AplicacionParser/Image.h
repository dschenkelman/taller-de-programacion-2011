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
	Image(int width, int height); // Empty image constructor
	~Image(void);
	SDL_Surface* getSDLSurface(void);
	int getWidth(void);
	int getHeight(void);
	Uint32 getPixel(int x, int y);
	void putPixel(Uint32 pixel, int x, int y);
	const SDL_PixelFormat* getFormat();
};
