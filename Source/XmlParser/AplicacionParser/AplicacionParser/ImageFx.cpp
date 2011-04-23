#include "stdafx.h"
#include "ImageFx.h"


Image* ImageFx::resize(Image *imgSrc, int widthDst, int heightDst){
	int width	= imgSrc->getWidth();
	int height	= imgSrc->getHeight();
	
	// Empty new image
	Image* imgDst = new Image(widthDst, heightDst);
	
	int stepsX = 0;
	for(int posYSrc = 0; posYSrc < height ; posYSrc++){
		
		int newY = (posYSrc * heightDst) / height;
		for(int posXSrc = 0; posXSrc < width; posXSrc++){

			// Obtengo el pixel de la imagen
			Uint32 pixelImg = imgSrc->getPixel(posXSrc, posYSrc);

			int newX = (posXSrc * widthDst) / width;
			int antX = ((posXSrc-1) * widthDst) / width;
			if( posXSrc != 0 && widthDst > width ){
				
				// obtengo el pixel anterior
				Uint32 pixelAnt = imgSrc->getPixel(antX, newY);
				
				// Obtengo las coordenadas rgb del pixel
				Uint8 antR, antG, antB, futR, futG, futB;
				SDL_GetRGB(pixelAnt, imgSrc->getFormat(), &antR, &antG, &antB);
				SDL_GetRGB(pixelImg, imgSrc->getFormat(), &futR, &futG, &futB);
				stepsX = (newX-antX);
				int range = stepsX-1;
				
				// Interpolo linealmente para obtener las nuevas coordenadas
				for (int i=1; i < stepsX; i++)
				{
					int j = range - i;
					int iR = ((antR * j) + (futR * i)) / range;
					int iG = ((antG * j) + (futG * i)) / range;
					int iB = ((antB * j) + (futB * i)) / range;
					
					// Obtengo el pixel de las coordenadas
					Uint32 pixelFut = SDL_MapRGB(imgDst->getFormat(), iR, iG, iB);
					
					// Coloco el pixel interpolado
					imgDst->putPixel( pixelFut,(antX+i), newY );
				}
			}

			if(posYSrc != 0 && heightDst > height ){
				int antY = ((posYSrc-1) * heightDst) / height;
				// obtengo el pixel anterior
				Uint32 pixelAnt = imgSrc->getPixel(newX, antY);
				
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
					for(int x = 0; x<stepsX; x++){
						imgDst->putPixel( pixelFut, (antX+1+x), (antY+i));
					}
				}
			}

			// Pongo el pixel en las nuevas coordenadas
			imgDst->putPixel( pixelImg, newX, newY);
		}
	}

	return imgDst;
}