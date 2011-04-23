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
	Image* imgSmile = new Image("smile.bmp");
	imgSmile->paste(screen, 100, 100);
	
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
