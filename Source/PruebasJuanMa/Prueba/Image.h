#include "sdl/sdl.h"
#include "Window.h"

#pragma once

class Image
{
public:
	/** Constructors */
	//Image(void);
	Image(char* uri);
	//Image(String uri, int x, int y, int width, int height);
	Image(int height, int width); // Empty image constructor
	
	void paste(SDL_Surface* board, int x, int y);
	void paste(Window board, int x, int y);
	void cropAndPaste(int x0, int y0, int width, int height, int x1, int y2, SDL_Surface* board);
	~Image(void);
	int getHeight();
	int getWidth();
	
	/** Get image's pixel at x and y */
	Uint32 getPixel(int x, int y);
	
	/** Put a pixel in this image at x and y */
	void putPixel(Uint32 pixel, int x, int y);
private:
	Image(SDL_Surface* surface);
	SDL_Surface* surface;
};
