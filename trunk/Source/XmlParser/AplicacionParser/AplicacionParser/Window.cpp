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
	//determina el tamaño
	SDL_Rect src;
	//determina la posicion
	SDL_Rect dest;
	src.x = 0;
	src.y = 0;
	src.w = image.getWidth();
	src.h = image.getHeight();
	dest.x = x;
	dest.y = y;
	
	//segun la doc w y h no se usan en dest
	//lo dejamos porque asi estan los ejemplos
	dest.w = image.getWidth();
	dest.h = image.getHeight();
	
	//http://sdl.beuc.net/sdl.wiki/SDL_BlitSurface
	SDL_BlitSurface(image.getSDLSurface(), &src, this->window, &dest);
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

