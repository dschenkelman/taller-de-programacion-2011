#include "StdAfx.h"
#include "Image.h"
#include "sdl/sdl.h"
#include "string.h"

Image::Image(void)
{
}

Image::Image(std::string uri)
{
	//this->surface = SDL_LoadBMP(uri);
}

Image::~Image(void)
{
	SDL_FreeSurface(this->surface);
}
