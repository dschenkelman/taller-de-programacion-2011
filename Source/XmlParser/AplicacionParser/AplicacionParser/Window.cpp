#include "StdAfx.h"
#include "Window.h"
#include "Image.h"
#include <string>
#include <exception>
#include <sstream>
#include "SDL.h"

using namespace std;

Window::Window(string t, int h, int w) : title(t), height(h), width(w), closed(false)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		stringstream msg;
		msg << "Unable to initialize SDL: " << SDL_GetError();
		throw std::exception(msg.str().c_str());
	}
 
	atexit(SDL_Quit);

	this->window = SDL_SetVideoMode(this->width, this->height, 24, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (this->window  == NULL) {
		stringstream msg;
		msg << "Unable to set video mode: " << SDL_GetError();
		throw std::exception(msg.str().c_str());
	}

	SDL_WM_SetCaption(this->title.c_str(), this->title.c_str());
}

void Window::close(void)
{
	this->closed = true;
	SDL_Quit();
}

void Window::display(Image& image, int x, int y)
{
	//Medida de seguridad, si se trata
	//de sacar la imagen de pantalla, la trato como circular.
	/*if ((x + image.getHeight()) > this->height){
		x-=image.getHeight();
	}
	if ((y + image.getWidth()) > this->width){
		y-=image.getWidth();
	}
	if ((x - image.getHeight()) < 0){
		x=0;
	}
	if ((y - image.getWidth()) < 0){
		y=0;
	}*/


	for (int i = 0; i < image.getWidth(); i++)
	{
		for (int j = 0; j < image.getHeight(); j++)
		{
			Uint32 pixel = image.getPixel(i, j);
			this->putPixel(pixel, (x + i), (y + j));
		}
	}
}

/** Get image's pixel at x and y */
Uint32 Window::getPixel(int x, int y) const
{
    int bpp = this->window->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)this->window->pixels + ((this->window->w * y + x) * bpp);

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
void Window::putPixel(Uint32 pixel, int x, int y)
{
	Window::putPixel(this->window, pixel, x, y);
}

void Window::putPixel(SDL_Surface *surface, Uint32 pixel, int x, int y)
{
	SDL_LockSurface(surface);
	int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) 
	{
		case 1:
			*p = pixel;
			break;

		case 2:
			*(Uint16 *)p = pixel;
			break;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) 
			{
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}
			else 
			{
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32 *)p = pixel;
			break;
    }

	SDL_UnlockSurface(surface);
}


void Window::refresh(void)
{
	SDL_Flip(this->window);
}
Window::~Window(void)
{
	//no hay que hacer free lo hace el SDL_Quit
	//SDL_FreeSurface(this->window);
	if (!this->closed)
	{ 
		this->close();
	}
}

