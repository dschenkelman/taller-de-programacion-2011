#include "StdAfx.h"
#include "Rotador.h"
#include <math.h>

Rotador::Rotador(void)
{
}

void Rotador::rotar(SDL_Surface* image, SDL_Surface* screen, int posX, int posY, double grados)
{
    if ( SDL_MUSTLOCK(screen) ) {
        if ( SDL_LockSurface(screen) < 0 ) {
            fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
        }
    }

	SDL_Flip(screen);

	SDL_Delay(1500);

	SDL_Rect dest;

	dest.x = 100;
	dest.y = 100;
	dest.h = image->h;
	dest.w = image->w;

	SDL_FillRect(screen,&dest,SDL_MapRGB(screen->format,0,0,0));
	SDL_UpdateRect(screen, 0, 0, 600, 400);

	int i = 0;

	while (i < image->h)
	{
		int j = 0;

		while (j < image->w)
		{
			Uint32 pixelImg = Resampler().getpixel(image, i, j);
			// se corrijen los ejes de coordenadas para pasar como parámetro

			if (i== 10 && j == 10)
			{
				int a = 2;
			}
			int nuevoX = rotarX(i - (image->w)/2, j - (image->h)/2, grados);
			int nuevoY = rotarY(i - (image->w)/2, j - (image->h)/2, grados);

			// se pone el pixel en la posicion nueva rotada y se le suma la posX e posY que son la posicion original de
			// la imagen en la screen
			Resampler().putpixel(screen, nuevoX + (image->w)/2 + posX, nuevoY + (image->h)/2 + posY, pixelImg);

			j++;
		}

		i++;
	}
	SDL_UpdateRect(screen, 0, 0, 600, 400);
}

int Rotador::rotarX(int x, int y, double grados)
{
	return (cos(grados) * x - sin(grados) * y);
}

int Rotador::rotarY(int x, int y, double grados)
{
	return sin(grados) * x + cos(grados) * y;
}

Rotador::~Rotador(void)
{
}
