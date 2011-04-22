#pragma once
#include "sdl/sdl.h"

class Resampler{
public:
	SDL_Surface* resample(SDL_Surface* imgSrc, int dstWidth, int dstHeight);
	Uint32 getpixel(SDL_Surface *surface, int x, int y);
	void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
};