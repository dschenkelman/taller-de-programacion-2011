#include "stdafx.h"
#include "resampler.h"
#include "sdl/sdl.h"
#include <math.h>


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

	int widthSrc	= imgSrc->getWidth();
	int heightSrc	= imgSrc->getHeight();
	
	// Empty new image
	Image* imgDst = new Image(widthDst, heightDst);
	
	// posiciones en la nueva imagen
	int posXDst = 0;
	int posYDst = 0;

	// iteracion filas
	for(int posYSrc = 0; posYSrc < heightSrc ; posYSrc++){
		
		// iteracion columnas
		for(int posXSrc = 0; posXSrc < widthSrc; posXSrc++){
			
			// obtengo las posiciones remappeadas en las nuevas dimensiones
			posXDst = (posXSrc * widthDst) / widthSrc;
			posYDst = (posYSrc * heightDst) / heightSrc;

			// Obtengo el pixel de la imagen
			Uint32 pixelImg = imgSrc->getPixel(posXSrc, posYSrc);

			// interpolacion
			if( posXSrc > 0 && posYSrc > 0 ){
				
				int fromY = (((posYSrc-1) * heightDst) / heightSrc);
				int fromX = (((posXSrc-1) * widthDst) / widthSrc);
				
				// interpolacion interna
				for (int y = fromY; y <= posYDst; y++){
					for (int x = fromX; x <= posXDst; x++){
						
						// pixel y posicion superior izquierdo
						Uint32 pixelSI = imgSrc->getPixel(posXSrc-1, posYSrc-1);
						int xSI = ((posXSrc-1) * widthDst) / widthSrc;
						int ySI = ((posYSrc-1) * heightDst) / heightSrc;
						// pixel y posicion superior derecho
						Uint32 pixelSD = imgSrc->getPixel(posXSrc, posYSrc-1);
						int xSD = (posXSrc * widthDst) / widthSrc;
						int ySD = ((posYSrc-1) * heightDst) / heightSrc;
						// pixel y posicion inferior izquierdo
						Uint32 pixelII = imgSrc->getPixel(posXSrc-1, posYSrc);
						int xII = ((posXSrc-1) * widthDst) / widthSrc;
						int yII = (posYSrc * heightDst) / heightSrc;

						// obtengo el pixel interpolado
						Uint32 interpolatedPixel = obtenerPixelInterpolado( pixelSI, xSI, ySI, 
																			pixelSD, xSD, ySD, 
																			pixelII, xII, yII, 
																			pixelImg, posXDst, posYDst, 
																			x, y,
																			imgDst );
						
						// coloco el pixel en la imagen destino
						imgDst->putPixel( interpolatedPixel, x, y );
					}
				}
			}

			// Pongo el pixel en las nuevas coordenadas
			imgDst->putPixel( pixelImg, posXDst, posYDst);
		}
	}

	return imgDst;
}


Uint32 Resampler::obtenerPixelInterpolado(Uint32 pixelSI, double xSI, double ySI, Uint32 pixelSD, double xSD, double ySD, Uint32 pixelII, double xII, double yII, Uint32 pixelID, double xID, double yID, double xNow, double yNow, Image* imgDst){
	
	// coordenadas RGB
	Uint8 rSI, gSI, bSI;
	Uint8 rSD, gSD, bSD;
	Uint8 rII, gII, bII;
	Uint8 rID, gID, bID;
	Uint8 rAfter, gAfter, bAfter;

	// obtengo las coordenadas RGB de los pixeles
	SDL_GetRGB(pixelSI, imgDst->getFormat(), &rSI, &gSI, &bSI);
	SDL_GetRGB(pixelSD, imgDst->getFormat(), &rSD, &gSD, &bSD);
	SDL_GetRGB(pixelII, imgDst->getFormat(), &rII, &gII, &bII);
	SDL_GetRGB(pixelID, imgDst->getFormat(), &rID, &gID, &bID);
	
	// interpolacion en y
	double	rYAfter1 = ( ((yII-yNow)/(yII-ySI))*rSI + ((yNow-ySI)/(yII-ySI))*rII );
	double	rYAfter2 = ( ((yII-yNow)/(yII-ySI))*rSD + ((yNow-ySI)/(yII-ySI))*rID );
	
	double	gYAfter1 = ( ((yII-yNow)/(yII-ySI))*gSI + ((yNow-ySI)/(yII-ySI))*gII );
	double	gYAfter2 = ( ((yII-yNow)/(yII-ySI))*gSD + ((yNow-ySI)/(yII-ySI))*gID );
	
	double	bYAfter1 = ( ((yII-yNow)/(yII-ySI))*bSI + ((yNow-ySI)/(yII-ySI))*bII );
	double	bYAfter2 = ( ((yII-yNow)/(yII-ySI))*bSD + ((yNow-ySI)/(yII-ySI))*bID );

	// interpolacion en x
	rAfter = (((xSD-xNow)/(xSD-xSI))*rYAfter1) + (((xNow-xSI)/(xSD-xSI))*rYAfter2);
	gAfter = ((xSD-xNow)/(xSD-xSI))*gYAfter1 + ((xNow-xSI)/(xSD-xSI))*gYAfter2;
	bAfter = ((xSD-xNow)/(xSD-xSI))*bYAfter1 + ((xNow-xSI)/(xSD-xSI))*bYAfter2;
		
	// Obtengo el pixel de las coordenadas
	Uint32 pixelFut = SDL_MapRGB(imgDst->getFormat(), rAfter, gAfter, bAfter);
	
	return pixelFut;
}
