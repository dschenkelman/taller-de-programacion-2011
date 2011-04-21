#include "StdAfx.h"
#include "Image.h"
#include "sdl/sdl.h"
#include "String.h"

Image::Image(void)
{
}

Image::Image(String uri)
{
	this->surface = SDL_LoadBMP(uri);
}

Image::~Image(void)
{
	SDL_FreeSurface(this->surface);
}
