#pragma once
#include <string>
#include "SDL.h"
#include <limits>

class Image
{
	SDL_Surface* image;
	bool error;
	std::string errorMessage;
	int height;
	int width;
	static void putPixel(SDL_Surface* surface, Uint32 pixel, int x, int y);
public:
	Image(std::string& path);
	Image(int width, int height); // Empty image constructor
	~Image(void);
	SDL_Surface* getSDLSurface(void);
	int getWidth(void);
	int getHeight(void);
	std::string getErrorMessage(void);
	bool hasError(void);
	Uint32 getPixel(int x, int y);
	void crop(int top, int left, int right, int bottom);
	void putPixel(Uint32 pixel, int x, int y);
	const SDL_PixelFormat* getFormat();
};
