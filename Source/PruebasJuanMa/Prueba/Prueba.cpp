// Prueba.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include <stdio.h>
#include <string> 
#include <iostream> 
#include <sstream>
#include "XMLParser.h"
#include "Obstaculo.h"
#include "Celda.h"
#include "Camino.h"
#include "Mapa.h"
#include "ScreenLogger.h"
#include <math.h>
#include "sdl/sdl.h"
#include "resampler.h"
#include "Window.h"
#include "Image.h"
#include "Rotador.h"

#define SDL_main main 

int rotateX(int xInicial, int yInicial,int xEje, int yEje, int grados){
	// corrijo el eje de referencia
	int xi = xInicial-xEje;
	int yi = yInicial-yEje;

	// roto los angulos
	int xf = ((xi*cos(double(grados)))-(yi*sin(double(grados))));
	
	// devuelvo el punto con su eje de coordenadas original
	return (xf+xEje);
}

int rotateY(int xInicial, int yInicial,int xEje, int yEje, int grados){
	// corrijo el eje de referencia
	int xi = xInicial-xEje;
	int yi = yInicial-yEje;

	// roto los angulos
	int yf = ((xi*sin(double(grados)))+(yi*cos(double(grados))));
	
	// devuelvo el punto con su eje de coordenadas original
	return (yf+yEje);
}


/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y)
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
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
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

void ejemploRotacion()
{
	SDL_Delay(2000);

	SDL_Surface* screen;
	SDL_Surface* image;
	SDL_Surface* temp;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		printf("No se pudo iniciar SDL: %s\n",SDL_GetError());
		exit(1);
	}

	screen = SDL_SetVideoMode(640,480,24,SDL_HWSURFACE);
	if (screen == NULL) {
		printf("No se puede inicializar el modo gráfico: \n",SDL_GetError());
		exit(1);
	}

	// Se carga la imagen
	temp = SDL_LoadBMP("smile.bmp");
	if (temp == NULL ) {
		printf("No pude cargar gráfico: %s\n", SDL_GetError());
		exit(1);
	}

	image = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	SDL_Rect dest;

	dest.x = 100;
	dest.y = 100;
	dest.h = image->h;
	dest.w = image->w;

	SDL_BlitSurface(image, NULL, screen, &dest);

	Rotador().rotar(image, screen, 100, 100, PI);
}

int main(int argc, char* argv[])
{
	//Window ventana = Window();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);

	SDL_Surface *screen;
	 
	screen = SDL_SetVideoMode(640, 480, 24, SDL_DOUBLEBUF);
	if (screen == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}

	Image sprite = Image("sprite.bmp");
	sprite.cropAndPaste(0,0,75,75,100,200,screen);
	sprite.cropAndPaste(85,75,75,75,200,200,screen);
	sprite.cropAndPaste(85,150,75,75,300,200,screen);

	SDL_Delay(1000);
	
	/** Agrandar imagen */

	// nueva imagen
	Image* imgSmile = new Image("pi.bmp");
	imgSmile->paste(screen, 50, 50);
	// Instancio un resampler
	Resampler* resampler = new Resampler();
	
	// Resampleo la imagen
	Image* imgResampled = resampler->resize(imgSmile, 100, 100);
	
	// Pego la imagen en la pantalla
	imgResampled->paste(screen, 0, 0);

	// ejemplo rotacion
	//ejemploRotacion();

	SDL_Delay(5000);
	
	// libero memoria
	free(imgSmile);
	free(imgResampled);
	free(resampler);
	 
	return 0;
}
