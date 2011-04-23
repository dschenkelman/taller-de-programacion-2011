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
	
	// bitmap
	SDL_Surface *image;
	SDL_Surface *temp;
	SDL_Surface *landImage;

	temp = SDL_LoadBMP("smile.bmp");
	if (temp == NULL) {
		printf("Unable to load bitmap: %s\n", SDL_GetError());
		return 1;
	}
	image = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	
	SDL_Rect src, dest;
	src.x = 0;
	src.y = 0;
	src.w = image->w;
	src.h = image->h;
	dest.x = 100;
	dest.y = 100;
	dest.w = image->w;
	dest.h = image->h;
	SDL_BlitSurface(image, &src, screen, &dest);
	SDL_Flip(screen);
	
	SDL_Delay(500);

	int x, y;
    
    x = screen->w / 2;
    y = screen->h / 2;

    // Lock the screen for direct access to the pixels 
    if ( SDL_MUSTLOCK(screen) ) {
        if ( SDL_LockSurface(screen) < 0 ) {
            fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
            return 0;
        }
    }

	// borro la imagen anterior
	SDL_FillRect(screen,&dest,SDL_MapRGB(screen->format,0,0,0));
	
	// Rotación de la imagen
	int i = 0;
	while( i < 20 ){
		int j = 0;
		while( j < 20){
			
			int xInicial = i;
			int yInicial = j;

			int xRot = rotateX(xInicial, yInicial, 10, 10, 10);
			int yRot = rotateY(xInicial, yInicial, 10, 10, 10);
			
			// Obtengo el pixel de la imagen
			Uint32 pixelImg = getpixel(image, xInicial, yInicial);

			// Pongo el pixel en la posicion rotada
			putpixel(screen, (100+xRot), (100+yRot), pixelImg);

			j++;
		}
		i++;
	}

	
	// actualizo la pantalla
	SDL_UpdateRect(screen, 0, 0, 600, 400);

    
	if ( SDL_MUSTLOCK(screen) ) {
        SDL_UnlockSurface(screen);
    }

	SDL_Delay(100);
	
	/* Agrandar imagen */
	// Instancio un resampler
	Resampler* resampler = new Resampler();
	
	// Resampleo la imagen
	SDL_Surface *imgResampled = resampler->resize(image, 100, 100);

	// La pego en la pantalla
	SDL_BlitSurface(imgResampled, NULL, screen, NULL);

	// actualizo la pantalla
	SDL_UpdateRect(screen, 0, 0, 600, 400);

	// ejemplo rotacion
	//ejemploRotacion();

	SDL_Delay(5000);
	free(resampler);
	 
	return 0;
}
