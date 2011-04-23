#include "StdAfx.h"
#include "Image.h"
#include "Window.h"
#include "sdl/sdl.h"


/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
static Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

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
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
static void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

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

/*Image::Image(void)
{
}*/

Image::Image(char* uri)
{
	this->surface = SDL_LoadBMP(uri);
	if (this->surface == NULL) {
		printf("Unable to load bitmap: %s\n", SDL_GetError());
	}

}

Image::Image(SDL_Surface* surface)
{
	this->surface = surface;
}


/** Empty Image constructor */
Image::Image(int width, int height){
	this->surface = SDL_CreateRGBSurface(SDL_SWSURFACE,width,height,24,0,0,0,0);
}


int Image::getHeight(){
	return this->surface->h;
}


int Image::getWidth(){
	return this->surface->w;
}


/** Get image's pixel at x and y */
Uint32 Image::getPixel(int x, int y){
    int bpp = this->surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)this->surface->pixels + y * this->surface->pitch + x * bpp;

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
    int bpp = this->surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)this->surface->pixels + y * this->surface->pitch + x * bpp;

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
	return this->surface->format;
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

void Image::cropAndPaste(int x0, int y0, int width, int height, int x1, int y2, SDL_Surface* board)
{
	int i, j;
	for (i=0;i<width;i++) {
		for (j=0;j<height;j++) {
			Uint32 pixelImg = getpixel(this->surface, i+x0, j+y0);
			putpixel(board, i+x1, j+y2, pixelImg);
		}
	}
}

Image::~Image(void)
{
	SDL_FreeSurface(this->surface);
}
