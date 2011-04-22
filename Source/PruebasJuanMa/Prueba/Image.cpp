#include "StdAfx.h"
#include "Image.h"
#include "Window.h"
#include "sdl/sdl.h"

/*Image::Image(void)
{
}*/

Image::Image(char* uri)
{
	this->surface = SDL_LoadBMP(uri);
}

void Image::paste(SDL_Surface* board, int x, int y)
{
	SDL_Rect src, dest;
	src.x = 0;
	src.y = 0;
	src.w = this->surface->w;
	src.h = this->surface->h;
	dest.x = x;
	dest.y = y;
	dest.w = this->surface->w;
	dest.h = this->surface->h;
	SDL_BlitSurface(this->surface, &src, board, &dest);
	SDL_Flip(board);
}

void Image::paste(Window windowBoard, int x, int y)
{
	SDL_Surface* board = windowBoard.getSDL_Surface();
	SDL_Rect src, dest;
	src.x = 0;
	src.y = 0;
	src.w = this->surface->w;
	src.h = this->surface->h;
	dest.x = x;
	dest.y = y;
	dest.w = this->surface->w;
	dest.h = this->surface->h;
	SDL_BlitSurface(this->surface, &src, board, &dest);
	SDL_Flip(board);
}

Image::~Image(void)
{
	SDL_FreeSurface(this->surface);
}
