#pragma once
#include <string>
#include "SDL.h"
#include "Image.h"

class Window
{
	bool closed;
	int height;
	int width;
	SDL_Surface* window;	
	std::string title;
	Uint32 getPixel(int x, int y) const;
	void putPixel(Uint32 pixel, int x, int y);
	void putPixel(SDL_Surface *surface, Uint32 pixel, int x, int y);
public:
	Window(std::string, int h, int w);
	void close(void);
	void refresh(void);
	void display(Image& image, int x, int y);
	~Window(void);
};