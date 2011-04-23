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

/** Empty Image constructor */
Image::Image(int width, int height){
	this->image = SDL_CreateRGBSurface(SDL_SWSURFACE,width,height,24,0,0,0,0);
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

/** Get image's pixel at x and y */
Uint32 Image::getPixel(int x, int y){
    int bpp = this->image->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)this->image->pixels + y * this->image->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;
    }
}


/** Put a pixel in this image at x and y */
void Image::putPixel(Uint32 pixel, int x, int y){
    int bpp = this->image->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)this->image->pixels + y * this->image->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}


const SDL_PixelFormat* Image::getFormat(){
	return this->image->format;
}