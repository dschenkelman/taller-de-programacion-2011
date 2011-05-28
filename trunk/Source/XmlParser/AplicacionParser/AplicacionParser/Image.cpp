#include "StdAfx.h"
#include "Image.h"
#include <string>
#include <sstream>
#include <limits>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "PixelHelpers.h"
#define PI 3.141592653589793238462643383279

using namespace std;

Image::Image(void) : width(0), height(0), error(false), errorMessage(""), image(NULL)
{
	/*this->image = SDL_CreateRGBSurface(SDL_HWSURFACE,width,height,24,0,0,0,0);*/
}


Image::Image(string path): height(0), width(0), error(false), errorMessage(""), image(NULL)
{
	this->image = SDL_LoadBMP(path.c_str());

	if (this->image == NULL ) 
	{
		this->error = true;
		stringstream msg;
		msg << "Error al abrir la imagen: " << SDL_GetError();
		this->errorMessage = msg.str();
	}
	else
	{
		this->width = this->image->w;
		this->height = this->image->h;
	}
}

/** Empty Image constructor */
Image::Image(int w, int h) : width(w), height(h), error(false), errorMessage(""), image(NULL)
{
	this->image = SDL_CreateRGBSurface(SDL_HWSURFACE,width,height,24,0,0,0,0);
}

//Image::Image(const Image& other) : height(0), width(0), error(false), errorMessage(""), image(NULL)
//{
//	this->copy(other);
//}

Image& Image::operator =(const Image& other)
{
	if (this == &other) 
	{
		return *this;
	}

	this->height = other.getHeight();
	this->width = other.getWidth();
	this->copy(other);

	return *this;
}

SDL_Surface* Image::getSDLSurface(void) const
{
	return this->image;
}

int Image::getHeight(void) const
{
	return this->height;
}

int Image::getWidth(void) const
{
	return this->width;
}

Image::~Image(void)
{
	SDL_FreeSurface(this->image);
	this->image = NULL;
}

/** Get image's pixel at x and y */
Uint32 Image::getPixel(int x, int y) const{
	return Image::getPixel(this->image, x, y);
}

Uint32 Image::getPixel(SDL_Surface* surface, int x, int y)
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


/** Put a pixel in this image at x and y */
void Image::putPixel(Uint32 pixel, int x, int y)
{
	Image::putPixel(this->image, pixel, x, y);
}

void Image::putPixel(SDL_Surface *surface, Uint32 pixel, int x, int y)
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



double Image::xRotatePixel(double radians, double x, double y)
{
	double zero = 0.000000000001;
	double c = cos(radians);
	double s = sin(radians);
	c = abs(c) < zero ? 0 : c;
	s = abs(s) < zero ? 0 : s;
	double real = (c * x + s * y);
	return real;
}

double Image::yRotatePixel(double radians, double x, double y)
{
	double zero = 0.000000000001;
	double c = cos(radians);
	double s = sin(radians);
	c = abs(c) < zero ? 0 : c;
	s = abs(s) < zero ? 0 : s;
	double real = c * y - s * x;
	return real;
}
const SDL_PixelFormat* Image::getFormat() const{
	return this->image->format;
}

string Image::getErrorMessage(void) const
{
	return this->errorMessage;
}

bool Image::hasError(void) const
{
	return this->error;
}

void Image::crop(int top, int left, int right, int bottom)
{
	stringstream out;

	if (this->hasError())
		return;
	if(right == numeric_limits<int>::max())
	{
		right = this->image->w;
	}

	if(bottom == numeric_limits<int>::max())
	{
		bottom = this->image->h;
	}

//Para que no se pasa de los límites de la imagen
	if (left < 0 )
		left=0;
	if (top < 0)
		top=0;
	if (right > this->image->w)
		right=this->image->w;
	if (bottom > this->image->h)
		bottom= this->image->h;

	//Acá esta mal los parametros
	if ((left > right) || (right < left) || (top > bottom) || (bottom < top) )
	{
		this->error=true;
		this->errorMessage="Coordenadas inválidas para relizar el recorte" ;
	}


	int newWidth = right - left;
	int newHeight = bottom - top;

	
	if (newWidth != this->getWidth() || newHeight != this->getHeight())
	{
		//needs to be resized
		SDL_Surface* temp = SDL_CreateRGBSurface(SDL_HWSURFACE, newWidth, newHeight, 24, 0, 0, 0, 0);

		for (int i = 0; i < newWidth; i++) 
		{
			for (int j = 0; j < newHeight; j++) 
			{
				Uint32 pixelImg = this->getPixel(left + i, top + j);
				Image::putPixel(temp, pixelImg, i, j);
			}
		}

		SDL_FreeSurface(this->image);
		this->image = temp;
		this->width = newWidth;
		this->height = newHeight;
	}
}

void Image::copy(const Image& other)
{
	SDL_Surface* temp = SDL_CreateRGBSurface(SDL_HWSURFACE, other.getWidth(), other.getHeight(), 24, 0, 0, 0, 0);

	for (int i = 0; i <  other.getWidth(); i++) 
	{
		for (int j = 0; j < other.getHeight(); j++) 
		{
			Uint32 pixelImg = other.getPixel(i, j);
			Image::putPixel(temp, pixelImg, i, j);
		}
	}

	this->height = other.getHeight();
	this->width = other.getWidth();
	this->error=other.hasError();
	this->errorMessage=other.getErrorMessage();

	if (this->image != NULL)
	{
		SDL_FreeSurface(this->image);
		this->image = NULL;
	}

	this->image = temp;
}

bool Image::validLimits(int x, int y)
{
	if (x < 0 || x >= this->width)
	{
		return false;
	}

	if (y < 0 || y >= this->height)
	{
		return false;
	}

	return true;
}

void Image::rotate(int degrees, Uint32 alpha)
{
	if (this->hasError())
		return;

	if (degrees == 0)
	{
		return;
	}
	
	int originalHeight = this->getHeight();
	int originalWidth = this->getWidth();

	if (originalHeight == 1 || originalWidth == 1)
	{
		this->resizeOnePixelImage();
	}

	//this->resize(originalWidth*(2), originalHeight*(2));
	double radians = ((degrees / 180.0) * PI);

	double originalCenterX = (this->getWidth() - 1)/ 2.0 ;
	double originalCenterY = (this->getHeight() -1) / 2.0;

	int rotatedHeight = this->getRotatedHeight(radians);
	int rotatedWidth = this->getRotatedWidth(radians);
	double rotatedCenterX = (rotatedWidth - 1) / 2.0;
	double rotatedCenterY = (rotatedHeight - 1) / 2.0;

	SDL_Surface* temp = SDL_CreateRGBSurface(SDL_HWSURFACE, rotatedWidth, rotatedHeight,24,0,0,0,0);
	
	for (int j = 0; j < rotatedHeight; j++) 
	{
		for (int i = 0; i < rotatedWidth; i++) 
		{
			double originalX = xRotatePixel(-radians, i - rotatedCenterX, j - rotatedCenterY);
			double originalY = yRotatePixel(-radians, i - rotatedCenterX, j - rotatedCenterY);

			originalX += originalCenterX;
			originalY += originalCenterY;

			if(!this->validLimits(originalX, originalY))
			{
				if ((int)originalX == originalX && (int)originalY == originalY)
				{
					if(originalX == this->width)
					{
						originalX--;
					}

					if(originalY == this->height)
					{
						originalY--;
					}

					Image::putPixel(temp, this->getPixel(originalX, originalY), i, j);
					continue;
				}
				else
				{
					Image::putPixel(temp, alpha, i, j);
				}
				continue;
			}

			Uint32 izq, der, inf, sup;
			izq = this->getPixel(originalX, originalY);
			sup = this->getPixel(originalX, originalY);

			if (this->validLimits(originalX + 1, originalY))
			{
				der = this->getPixel(originalX+1, originalY);
			}
			else
			{
				der = this->getPixel(originalX, originalY);;
			}					

			if (this->validLimits(originalX, originalY + 1))
			{
				inf = this->getPixel(originalX, originalY + 1);
			}
			else
			{
				inf = this->getPixel(originalX, originalY);;
			}

			// obtengo el pixel interpolado
			Uint32 interpolatedPixel = this->getInterpolatedPixel
				(sup, originalX, originalY, 
				der, originalX+1, originalY, 
				inf, originalX, originalY+1, 
				izq, originalX, originalY, 
				originalX, originalY, this->getFormat());

			Image::putPixel(temp, interpolatedPixel, i, j);
		}
	}

	//int originalHeight = this->getHeight();
	//int originalWidth = this->getWidth();

	SDL_FreeSurface(this->image);
	this->image = temp;
	this->width = rotatedWidth;
	this->height = rotatedHeight;
	/*this->resize(originalWidth, originalHeight);*/
}


int reMappedPos(int posSrc, int maxSrc, int maxDst){
	int porcentaje = (posSrc*100)/maxSrc;
	return ((porcentaje*maxDst)/100);
}


void Image::resize(int newWidth, int newHeight)
{
	if (this->hasError())
		return;

	int widthSrc	= this->getWidth();
	int heightSrc	= this->getHeight();
	
	if (widthSrc == 1 || heightSrc == 1)
	{
		this->resizeOnePixelImage();
		widthSrc = this->getWidth();
		heightSrc = this->getHeight();
	} 

	// Empty new image
	SDL_Surface* temp = SDL_CreateRGBSurface(SDL_HWSURFACE,newWidth,newHeight,24,0,0,0,0);
	
	// posiciones en la nueva imagen
	int posXDst = 0;
	int posYDst = 0;

	// iteracion filas
	for(int posYSrc = 0; posYSrc < heightSrc ; posYSrc++){
		
		// iteracion columnas
		for(int posXSrc = 0; posXSrc < widthSrc; posXSrc++){
			
			// obtengo las posiciones remappeadas en las nuevas dimensiones
			posXDst = reMappedPos(posXSrc, (widthSrc-1), (newWidth-1));
			posYDst = reMappedPos(posYSrc, (heightSrc-1), (newHeight-1));

			// Obtengo el pixel de la imagen
			Uint32 pixelImg = this->getPixel(posXSrc, posYSrc);

			// interpolacion
			if( posXSrc > 0 && posYSrc > 0 ){
				
				int fromX = reMappedPos((posXSrc-1), (widthSrc-1), (newWidth-1));
				int fromY = reMappedPos((posYSrc-1), (heightSrc-1), (newHeight-1));
				
				// interpolacion interna
				for (int y = fromY; y <= posYDst; y++){
					for (int x = fromX; x <= posXDst; x++){
						
						// pixel y posicion superior izquierdo
						Uint32 pixelSI = this->getPixel(posXSrc-1, posYSrc-1);
						int xSI = fromX;
						int ySI = fromY;
						// pixel y posicion superior derecho
						Uint32 pixelSD = this->getPixel(posXSrc, posYSrc-1);
						int xSD = posXDst;
						int ySD = fromY;
						// pixel y posicion inferior izquierdo
						Uint32 pixelII = this->getPixel(posXSrc-1, posYSrc);
						int xII = fromX;
						int yII = posYDst;

						// obtengo el pixel interpolado
						Uint32 interpolatedPixel = this->getInterpolatedPixel( pixelSI, xSI, ySI, 
																			pixelSD, xSD, ySD, 
																			pixelII, xII, yII, 
																			pixelImg, posXDst, posYDst, 
																			x, y, this->getFormat());
						
						// coloco el pixel en la imagen destino
						Image::putPixel(temp, interpolatedPixel, x, y);
						/*temp.putPixel( interpolatedPixel, x, y );*/
					}
				}
			}

			// Pongo el pixel en las nuevas coordenadas
			Image::putPixel(temp, pixelImg, posXDst, posYDst);		
			/*temp.putPixel( pixelImg, posXDst, posYDst);*/
		}
	}
	
	SDL_FreeSurface(this->image);
	this->image = temp;
	this->width = newWidth;
	this->height = newHeight;
}


Uint32 Image::getInterpolatedPixel(Uint32 pixelSI, double xSI, double ySI, Uint32 pixelSD, double xSD, double ySD, Uint32 pixelII, double xII, double yII, Uint32 pixelID, double xID, double yID, double xNow, double yNow, const SDL_PixelFormat* newFormat){
	
	// coordenadas RGB
	Uint8 rSI, gSI, bSI;
	Uint8 rSD, gSD, bSD;
	Uint8 rII, gII, bII;
	Uint8 rID, gID, bID;
	Uint8 rAfter, gAfter, bAfter;

	// obtengo las coordenadas RGB de los pixeles
	SDL_GetRGB(pixelSI, newFormat, &rSI, &gSI, &bSI);
	SDL_GetRGB(pixelSD, newFormat, &rSD, &gSD, &bSD);
	SDL_GetRGB(pixelII, newFormat, &rII, &gII, &bII);
	SDL_GetRGB(pixelID, newFormat, &rID, &gID, &bID);
	
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
	Uint32 pixelFut = SDL_MapRGB(newFormat, rAfter, gAfter, bAfter);
	
	return pixelFut;
}

int Image::getRotatedWidth(double radians)
{
	double centerX = this->getWidth() / 2.0;		
	double centerY = this->getHeight() / 2.0;

	double rotatedTopLeftX = xRotatePixel(radians, -centerX, -centerY);
	
	double rotatedTopRightX = xRotatePixel(radians, centerX, -centerY);
	
	double rotatedBottomRightX = xRotatePixel(radians, centerX, centerY);
	
	double rotatedBottomLeftX = xRotatePixel(radians, -centerX, centerY);

	double xValues[4] = {rotatedBottomLeftX, rotatedBottomRightX, rotatedTopLeftX, rotatedTopRightX};
	
	double xMax = *max_element(xValues, xValues + 4);
	double xMin = *min_element(xValues, xValues + 4);

	return xMax - xMin;
}

int Image::getRotatedHeight(double radians)
{
	double centerX = this->getWidth() / 2.0;		
	double centerY = this->getHeight() / 2.0;

	double rotatedTopLeftY = yRotatePixel(radians, -centerX, -centerY);
	
	double rotatedTopRightY = yRotatePixel(radians, centerX, -centerY);
	
	double rotatedBottomRightY = yRotatePixel(radians, centerX, centerY);
	
	double rotatedBottomLeftY = yRotatePixel(radians, -centerX, centerY);

	double yValues[4] = {rotatedBottomLeftY, rotatedBottomRightY, rotatedTopLeftY, rotatedTopRightY};
	
	double yMax = *max_element(yValues, yValues + 4);
	double yMin = *min_element(yValues, yValues + 4);

	return yMax - yMin;
}

void Image::superImpose(Image& imageToImpose, int alphaRed, int alphaGreen, int alphaBlue, int delta){

	//Caso feliz:
	//Una imagen es mas grande que la otra por superfice, ya que siempre son cuadradas.
	//Si se da el caso de que la nueva es mas grande que la actual, hago un resize de la nueva y se la 
	//asigno pixel a pixel a la vieja.

	if (this->hasError() || imageToImpose.hasError()){
		if ( imageToImpose.hasError()){
			this->error=(this->error || imageToImpose.hasError());
			this->errorMessage= "No se pudo abrir la imagen del bonus: "+imageToImpose.getErrorMessage();
		}
		return;
	}
	int anchoImagen,altoImagen,altoPantalla,anchoPantalla,inicioAnchoPantalla,inicioAltoPantalla;
	
	anchoImagen=altoImagen=altoPantalla=anchoPantalla=0;
	
	anchoPantalla=this->getWidth();
	altoPantalla=this->getHeight();

	altoImagen=imageToImpose.getHeight();
	anchoImagen=imageToImpose.getWidth();


	long areaToImpose=altoImagen * anchoImagen;
	long currentImageArea= anchoPantalla * altoPantalla;

	if (areaToImpose > currentImageArea)
	{
		//resize de la imagen a transparentar en caso de que sea mayor en area que la actual.
		imageToImpose.resize(this->getWidth(), this->getHeight());
		altoImagen = this->getHeight();
		anchoImagen = this->getWidth();
	//	this->copy(imageToImpose);
	}
	/*else{*/

	//Calculo el x e y inicial donde ubicar la imagen para centrarlo.
	//Lo ubico pixela pixel.
	inicioAnchoPantalla= (anchoPantalla - anchoImagen) / 2;
	inicioAltoPantalla= (altoPantalla - altoImagen) / 2;

	for (int i = 0; i < anchoPantalla; i++) 
	{
		for (int j = 0; j < altoPantalla; j++) 
		{
			if ( (i >= inicioAnchoPantalla) &&	(i < (inicioAnchoPantalla + anchoImagen)) &&
				(j >= inicioAltoPantalla) && (j < (inicioAltoPantalla + altoImagen)) )
				
			{
				//Pixel de la imagen a sobreimponer
				Uint32 pixelAImponer=imageToImpose.getPixel(i-inicioAnchoPantalla,j-inicioAltoPantalla);
				int deltaPixel = PixelHelpers::getDeltaBetweenPixels(alphaRed, alphaGreen, alphaBlue, pixelAImponer);
				if (deltaPixel > delta)
				{
					Image::putPixel(pixelAImponer, i, j);
				}
			}
		}
		//}

	}

	return;
}

void Image::resizeOnePixelImage()
{
	int currentWidth = this->getWidth();
	int currentHeight = this->getHeight();

	if (currentWidth == 1)
	{
		SDL_Surface* temp = SDL_CreateRGBSurface(SDL_HWSURFACE, 2, currentHeight, 24,0,0,0,0);
		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < currentHeight; y++)
			{
				Uint32 p = this->getPixel(0, y);
				this->putPixel(temp, p, x, y);
			}
		}

		if (this->image != NULL)
		{
			SDL_FreeSurface(this->image);
		}
		this->image = temp;
		this->width = temp->w;
		this->height = temp->h;

		currentWidth = this->getWidth();
		currentHeight = this->getHeight();
	}

	if (currentHeight == 1)
	{
		SDL_Surface* temp = SDL_CreateRGBSurface(SDL_HWSURFACE, currentWidth, 2, 24,0,0,0,0);
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < currentWidth; x++)
			{
				Uint32 p = this->getPixel(x, 0);
				this->putPixel(temp, p, x, y);
			}
		}

		if (this->image != NULL)
		{
			SDL_FreeSurface(this->image);
		}
		this->image = temp;
		this->width = temp->w;
		this->height = temp->h;
	}
}

void Image::display(Image& image, int x, int y, int red, int green, int blue, int delta)
{
	for (int i = 0; i < image.getWidth(); i++)
	{
		for (int j = 0; j < image.getHeight(); j++)
		{
			Uint32 overPixel = image.getPixel(i, j);
			int deltaPixel = PixelHelpers::getDeltaBetweenPixels(red, green, blue, overPixel);
			if (deltaPixel > delta)
			{
				this->putPixel(overPixel, (x + i), (y + j));
			}
		}
	}
}