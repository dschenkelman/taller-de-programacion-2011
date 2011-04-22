#include "stdafx.h"
#include "resampler.h"
#include "sdl/sdl.h"


Uint32 Resampler::getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
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
        return 0;       
    }
}


void Resampler::putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
   
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


SDL_Surface* Resampler::resample(SDL_Surface* imgSrc, int dstWidth, int dstHeight){
	
	// Por ahora no se usa la altura futura, solo el aumento general
	int aumento = 1;

	int ancho	= imgSrc->w;
	int alto	= imgSrc->h;
	int nuevoAncho		= (((aumento*2)+1)*ancho);
	int nuevoAlto		= (((aumento*2)+1)*alto);

	SDL_Surface *imagenDestino = SDL_CreateRGBSurface(SDL_SWSURFACE,nuevoAncho,nuevoAlto,24,0,0,0,0);


	int nuevaFil = -1;
	int nuevaCol = -1;
	int anteriorFil = -1;
	int anteriorCol = -1;
	int fila = 0;	
	while( fila < alto ){
		int columna = 0;
		if(anteriorFil == -1){
			nuevaFil = aumento;
		}else{
			nuevaFil = (anteriorFil + (aumento * 2)) + 1;
		}
		while( columna < ancho){

			if(anteriorCol == -1){
				nuevaCol = aumento;
			}else{
				nuevaCol = (anteriorCol + (aumento * 2)) + 1;
			}
			
			// Obtengo el pixel de la imagen
			Uint32 pixelImg = getpixel(imgSrc, fila, columna);

			if((columna != 0)){
				// obtengo el pixel anterior
				Uint32 pixelAnt = getpixel(imgSrc, anteriorFil, anteriorCol);
				
				// Obtengo las coordenadas rgb del pixel
				Uint8 antR, antG, antB, futR, futG, futB;
				SDL_GetRGB(pixelAnt, imgSrc->format, &antR, &antG, &antB);
				SDL_GetRGB(pixelImg, imgSrc->format, &futR, &futG, &futB);
				int steps = 2;
				int range = steps-1;
				
				// Interpolo linealmente para obtener las nuevas coordenadas
				for (int i=0; i < steps; i++)
				{
					int j = range - i;
					int iR = ((antR * j) + (futR * i)) / range;
					int iG = ((antG * j) + (futG * i)) / range;
					int iB = ((antB * j) + (futB * i)) / range;
					
					// Obtengo el pixel de las coordenadas
					Uint32 pixelFut = SDL_MapRGB(imagenDestino->format, iR, iG, iB);
					
					// Coloco el pixel interpolado
					putpixel(imagenDestino, nuevaFil, anteriorCol+i, pixelFut);
				}
			}
			
			// Pongo el pixel en la posicion rotada
			putpixel(imagenDestino, nuevaFil, nuevaCol, pixelImg);
			anteriorCol = nuevaCol;
			columna++;
		}
		anteriorCol = -1;
		anteriorFil = nuevaFil;
		fila++;
	}
	
	return imagenDestino;
}