#pragma once
#include "Image.h"
#include "resampler.h"
#include "Window.h"
#include "sdl/sdl.h"
#define PI 3.14159265

class Rotador
{
public:
	Rotador(void);
	void rotar(SDL_Surface* image, SDL_Surface* screen, int posX, int posY, double grados);
	~Rotador(void);
	int rotarX(int x, int y, double grados);
	int rotarY(int x, int y, double grados);
};
