#include "StdAfx.h"
#include "Image.h"
#include <string>
#include <sstream>

using namespace std;

Image::Image(string& path)
{
	this->image = SDL_LoadBMP(path.c_str());
	if (this->image == NULL) 
	{
		stringstream msg;
		msg << "Unable to load bitmap: " << SDL_GetError();
		throw std::exception(msg.str().c_str());	
	}

	this->width = this->image->w;
	this->height = this->image->h;
}

SDL_Surface* Image::getSDLSurface(void)
{
	return this->image;
}

int Image::getHeight(void)
{
	return this->height;
}

int Image::getWidth(void)
{
	return this->width;
}

Image::~Image(void)
{
	SDL_FreeSurface(this->image);
}

