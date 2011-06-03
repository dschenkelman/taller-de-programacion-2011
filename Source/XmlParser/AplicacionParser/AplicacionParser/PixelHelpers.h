#pragma once
#include "sdl/sdl.h"

class PixelHelpers
{
public:
	PixelHelpers(void);
	static int getDeltaBetweenPixels(int red, int green, int blue, Uint32 pixelAImponer);
	~PixelHelpers(void);
};
