#pragma once
#include "sdl/sdl.h"
#include "Image.h"

class Resampler{
public:
	Uint32 getpixel(SDL_Surface *surface, int x, int y);
	void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
	Image resize(Image srcImg, int dstHeight, int dstWidth);
};