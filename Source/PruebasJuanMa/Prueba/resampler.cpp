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



Image* Resampler::resize(Image* imgSrc, int widthDst, int heightDst){

	int width	= imgSrc->getWidth();
	int height	= imgSrc->getHeight();
	
	// Empty new image
	Image* imgDst = new Image(widthDst, heightDst);
	
	
	for(int posYSrc = 0; posYSrc < height ; posYSrc++){
		
		int newY = (posYSrc * heightDst) / height;
		for(int posXSrc = 0; posXSrc < width; posXSrc++){

			// Obtengo el pixel de la imagen
			Uint32 pixelImg = imgSrc->getPixel(posXSrc, posYSrc);

			int newX = (posXSrc * widthDst) / width;
			int antX = ((posXSrc-1) * widthDst) / width;
			int proX = ((posXSrc+1) * widthDst) / width;
			int stepsX = (proX-newX)/2;
			if( posXSrc != 0 && widthDst > width ){
				
				// obtengo el pixel anterior
				Uint32 pixelAnt = imgSrc->getPixel((posXSrc-1), posYSrc);
				stepsX = newX-antX;
				// Obtengo las coordenadas rgb del pixel
				Uint8 antR, antG, antB, futR, futG, futB;
				SDL_GetRGB(pixelAnt, imgSrc->getFormat(), &antR, &antG, &antB);
				SDL_GetRGB(pixelImg, imgSrc->getFormat(), &futR, &futG, &futB);
				int range = stepsX-1;
				
				// Interpolo linealmente para obtener las nuevas coordenadas
				for (int i=0; i < range; i++)
				{
					int j = range - i;
					int iR = ((antR * j) + (futR * i)) / range;
					int iG = ((antG * j) + (futG * i)) / range;
					int iB = ((antB * j) + (futB * i)) / range;
					
					// Obtengo el pixel de las coordenadas
					Uint32 pixelFut = SDL_MapRGB(imgDst->getFormat(), iR, iG, iB);
					
					// Coloco el pixel interpolado
					imgDst->putPixel( pixelFut,(antX+1+i), newY );
				}
			}

			if(posYSrc != 0 && heightDst > height ){
				
				int antY = ((posYSrc-1) * heightDst) / height;
				// obtengo el pixel anterior
				Uint32 pixelAnt = imgSrc->getPixel(posXSrc, (posYSrc-1));
				
				// Obtengo las coordenadas rgb del pixel
				Uint8 antR, antG, antB, futR, futG, futB;
				SDL_GetRGB(pixelAnt, imgSrc->getFormat(), &antR, &antG, &antB);
				SDL_GetRGB(pixelImg, imgSrc->getFormat(), &futR, &futG, &futB);
				int steps = (newY-antY);
				int range = steps-1;
				
				// Interpolo linealmente para obtener las nuevas coordenadas
				for (int i=1; i < steps; i++)
				{
					int j = range - i;
					int iR = ((antR * j) + (futR * i)) / range;
					int iG = ((antG * j) + (futG * i)) / range;
					int iB = ((antB * j) + (futB * i)) / range;
					
					// Obtengo el pixel de las coordenadas
					Uint32 pixelFut = SDL_MapRGB(imgDst->getFormat(), iR, iG, iB);
					
					// Coloco el pixel interpolado
					if(posXSrc == 0){
						int hastaX = (stepsX/2);
						for(int k = 0; k<hastaX; k++){
							imgDst->putPixel( pixelFut, k, (antY+i));
						}
					}else{
						int hastaX = (antX+1);
						for(int k = hastaX; k <= newX; k++){
							imgDst->putPixel( pixelFut, k, (antY+i));
						}
					}
				}
			}

			// Pongo el pixel en las nuevas coordenadas
			imgDst->putPixel( pixelImg, newX, newY);
		}
	}

	return imgDst;
}