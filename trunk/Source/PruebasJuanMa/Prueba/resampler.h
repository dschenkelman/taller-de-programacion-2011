#pragma once
#include "sdl/sdl.h"
#include "Image.h"

class Resampler{
public:
	Uint32 getpixel(SDL_Surface *surface, int x, int y);
	void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
	Image* resize(Image* srcImg, int dstHeight, int dstWidth);
private:
	Uint32 obtenerPixelInterpolado(Uint32 pixelSI, double xSI, double ySI, Uint32 pixelSD, double xSD, double ySD, Uint32 pixelII, double xII, double yII, Uint32 pixelID, double xID, double yID, double xNow, double yNow, Image* imgDst);
};