#include "sdl/sdl.h"
#include "Window.h"

#pragma once

class Image
{
public:
	//Image(void);
	Image(char* uri);
	//Image(String uri, int x, int y, int width, int height);
	void paste(SDL_Surface* board, int x, int y);
	void paste(Window board, int x, int y);
	void cropAndPaste(int x0, int y0, int width, int height, int x1, int y2, SDL_Surface* board);
	~Image(void);
private:
	Image(SDL_Surface* surface);
	SDL_Surface* surface;
};
