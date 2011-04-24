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
	Image(std::string path);
	Image(int width, int height); // Empty image constructor
	Image(const Image& other);
	Image& operator=(const Image& other);
	~Image(void);
	SDL_Surface* getSDLSurface(void) const;
	int getWidth(void) const;
	int getHeight(void) const;
	std::string getErrorMessage(void) const;
	bool hasError(void) const;
	Uint32 getPixel(int x, int y) const;
	void crop(int top, int left, int right, int bottom);
	void putPixel(Uint32 pixel, int x, int y);
	void copy(const Image& other);
	const SDL_PixelFormat* getFormat() const;
};
