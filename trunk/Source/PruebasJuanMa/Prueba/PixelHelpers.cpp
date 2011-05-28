#include "StdAfx.h"
#include "PixelHelpers.h"
#include "sdl/sdl.h"

PixelHelpers::PixelHelpers(void)
{
}

int PixelHelpers::getDeltaBetweenPixels(int red, int green, int blue, Uint32 p)
{
	int imposeRed;
	int imposeGreen;
	int imposeBlue;

	if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
			imposeRed = (p >> 16) & 255;
			imposeGreen = (p >> 8) & 255;
			imposeBlue = p & 255;
	}
	else
	{
            imposeRed = p & 255;
			imposeGreen = (p >> 8) & 255;
			imposeBlue = (p >> 16) & 255;
	}

	return abs(red - imposeRed) + abs(green-imposeGreen) + abs(blue - imposeBlue);
}

PixelHelpers::~PixelHelpers(void)
{
}
