#include "StdAfx.h"
#include "Image.h"
#include <string>
#include <sstream>
#include <limits>
#include <math.h>
#include <algorithm>
#define PI 3.14159265

using namespace std;

Image::Image(string path): height(0), width(0), error(false), errorMessage(""), image(NULL)
{
	this->image = SDL_LoadBMP(path.c_str());
	if (this->image == NULL) 
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

Image::Image(const Image& other) : height(0), width(0), error(false), errorMessage(""), image(NULL)
{
	this->copy(other);
}

Image& Image::operator =(const Image& other)
{
	if (this == &other) 
	{
		return *this;
	}

	this->height = other.getHeight();
	this->width = other.getWidth();
	this->error = other.hasError();
	this->errorMessage = other.getErrorMessage();

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
    int bpp = this->image->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)this->image->pixels + ((this->image->w * y + x) * bpp);

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
    Uint8 *p = (Uint8 *)surface->pixels + ((surface->w * y + x) * bpp);

    switch(bpp) 
	{
		case 1:
			*p = pixel;
			break;

		case 2:
			*(Uint16 *)p = pixel;
			break;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) 
			{
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}
			else 
			{
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



int Image::xRotatePixel(double radians, int x, int y)
{
	return cos(radians) * x + sin(radians) * y;                                                                                                                                                                                                                                                                                                                   
}

int Image::yRotatePixel(double radians, int x, int y)
{
	return cos(radians) * y - sin(radians) * x;
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
	if(right == numeric_limits<int>::max())
	{
		right = this->image->w;
	}

	if(bottom == numeric_limits<int>::max())
	{
		bottom = this->image->h;
	}


	int width = right - left;
	int height = bottom - top;


	if (width != this->getWidth() || height != this->getHeight())
	{
		//needs to be resized
		Image temp(width, height);

		for (int i = 0; i < width; i++) 
		{
			for (int j = 0; j < height; j++) 
			{
				Uint32 pixelImg = this->getPixel(left + i, top + j);
				temp.putPixel(pixelImg, i, j);
			}
		}

		this->copy(temp);
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

	if (this->image != NULL)
	{
		SDL_FreeSurface(this->image);
		this->image = NULL;
	}

	this->image = temp;
}

void Image::rotate(int degrees, Uint32 alpha)
{
	double radians = ((degrees / 180.0) * PI);

	int originalCenterX = this->getWidth() / 2;
	int originalCenterY = this->getHeight() / 2;

	int rotatedHeight = this->getRotatedHeight(radians);
	int rotatedWidth = this->getRotatedWidth(radians);
	int rotatedCenterX = rotatedWidth / 2;
	int rotatedCenterY = rotatedHeight / 2;

	Image temp(rotatedWidth, rotatedHeight);

	for (int i = 0; i < rotatedWidth; i++) 
	{
		for (int j = 0; j < rotatedHeight; j++) 
		{
			int originalX = xRotatePixel(-radians, i - rotatedCenterX, j - rotatedCenterY);
			int originalY = yRotatePixel(-radians, i - rotatedCenterX, j - rotatedCenterY);

			originalX += originalCenterX;
			originalY += originalCenterY;

			if(!validLimits(originalX, originalY))
			{
				temp.putPixel(alpha, i, j);
				continue;
			}

			Uint32 pixelImg = this->getPixel(originalX, originalY);
			temp.putPixel(pixelImg, i, j);
		}
	}

	int originalHeight = this->getHeight();
	int originalWidth = this->getWidth();

	this->copy(temp);
	this->resize(originalWidth, originalHeight);
}

bool Image::validLimits(int x, int y)
{
	if (x < 0 || x > this->width)
	{
		return false;
	}

	if (y < 0 || y > this->height)
	{
		return false;
	}

	return true;
}

/*void Image::rotate(int degrees, Uint32 alpha)
{
	double radians = ((degrees / 180.0) * PI);

	int rotatedHeight = this->getRotatedHeight(radians);
	int rotatedWidth = this->getRotatedWidth(radians);

	Image temp(rotatedWidth, rotatedHeight);

	int centerX = this->getWidth() / 2;		
	int centerY = this->getHeight() / 2;

	for (int i = 0; i < rotatedWidth; i++) 
	{
		for (int j = 0; j < rotatedHeight; j++) 
		{
			temp.putPixel(alpha, i, j);
		}
	}

	int newCenterX = rotatedWidth / 2;
	int newCenterY = rotatedHeight / 2;

	for (int i = 0; i <  this->getWidth(); i++) 
	{
		for (int j = 0; j < this->getHeight(); j++) 
		{
			Uint32 pixelImg = this->getPixel(i, j);
		
			int rotatedX = xRotatePixel(radians, i - centerX, j - centerY);
			int rotatedY = yRotatePixel(radians, i - centerX, j - centerY);
			int yPosition = rotatedY + newCenterY;
			int xPosition = rotatedX + newCenterX;

			if (yPosition < 0)
			{
				yPosition = 0;
			}

			if (xPosition < 0)
			{
				xPosition = 0;
			}

			if (xPosition >= rotatedWidth)
			{
				xPosition = rotatedWidth - 1;
			}

			if (yPosition >= rotatedHeight)
			{
				yPosition = rotatedHeight - 1;
			}

			temp.putPixel(pixelImg, xPosition, yPosition);
		}
	}

	int originalHeight = this->getHeight();
	int originalWidth = this->getWidth();

	this->copy(temp);
	this->resize(originalWidth, originalHeight);
}*/


void Image::resize(int newWidth, int newHeight)
{
	int widthSrc	= this->getWidth();
	int heightSrc	= this->getHeight();
	
	// Empty new image
	Image* temp = new Image(newWidth, newHeight);
	
	// posiciones en la nueva imagen
	int posXDst = 0;
	int posYDst = 0;

	// iteracion filas
	for(int posYSrc = 0; posYSrc < heightSrc ; posYSrc++){
		
		// iteracion columnas
		for(int posXSrc = 0; posXSrc < widthSrc; posXSrc++){
			
			// obtengo las posiciones remappeadas en las nuevas dimensiones
			posXDst = (posXSrc * newWidth) / widthSrc;
			posYDst = (posYSrc * newHeight) / heightSrc;

			// Obtengo el pixel de la imagen
			Uint32 pixelImg = this->getPixel(posXSrc, posYSrc);

			// interpolacion
			//if( posXSrc > 0 && posYSrc > 0 ){
			if( posXSrc > 0 && posYSrc > 0 && newWidth > widthSrc && newHeight > heightSrc ){
				
				int fromY = (((posYSrc-1) * newHeight) / heightSrc);
				int fromX = (((posXSrc-1) * newWidth) / widthSrc);
				
				// interpolacion interna
				for (int y = fromY; y <= posYDst; y++){
					for (int x = fromX; x <= posXDst; x++){
						
						// pixel y posicion superior izquierdo
						Uint32 pixelSI = this->getPixel(posXSrc-1, posYSrc-1);
						int xSI = ((posXSrc-1) * newWidth) / widthSrc;
						int ySI = ((posYSrc-1) * newHeight) / heightSrc;
						// pixel y posicion superior derecho
						Uint32 pixelSD = this->getPixel(posXSrc, posYSrc-1);
						int xSD = (posXSrc * newWidth) / widthSrc;
						int ySD = ((posYSrc-1) * newHeight) / heightSrc;
						// pixel y posicion inferior izquierdo
						Uint32 pixelII = this->getPixel(posXSrc-1, posYSrc);
						int xII = ((posXSrc-1) * newWidth) / widthSrc;
						int yII = (posYSrc * newHeight) / heightSrc;

						// obtengo el pixel interpolado
						Uint32 interpolatedPixel = this->getInterpolatedPixel( pixelSI, xSI, ySI, 
																			pixelSD, xSD, ySD, 
																			pixelII, xII, yII, 
																			pixelImg, posXDst, posYDst, 
																			x, y, temp->getFormat());
						
						// coloco el pixel en la imagen destino
						temp->putPixel( interpolatedPixel, x, y );
					}
				}
			}

			// Pongo el pixel en las nuevas coordenadas
			temp->putPixel( pixelImg, posXDst, posYDst);
		}
	}
	
	this->copy(*temp);
	free(temp);
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
	int centerX = this->getWidth() / 2;		
	int centerY = this->getHeight() / 2;

	int rotatedTopLeftX = xRotatePixel(radians, -centerX, -centerY);
	
	int rotatedTopRightX = xRotatePixel(radians, centerX, -centerY);
	
	int rotatedBottomRightX = xRotatePixel(radians, centerX, centerY);
	
	int rotatedBottomLeftX = xRotatePixel(radians, -centerX, centerY);

	int xValues[4] = {rotatedBottomLeftX, rotatedBottomRightX, rotatedTopLeftX, rotatedTopRightX};
	
	int xMax = *max_element(xValues, xValues + 4);
	int xMin = *min_element(xValues, xValues + 4);

	return xMax - xMin;
}

int Image::getRotatedHeight(double radians)
{
	int centerX = this->getWidth() / 2;		
	int centerY = this->getHeight() / 2;

	int rotatedTopLeftY = yRotatePixel(radians, -centerX, -centerY);
	
	int rotatedTopRightY = yRotatePixel(radians, centerX, -centerY);
	
	int rotatedBottomRightY = yRotatePixel(radians, centerX, centerY);
	
	int rotatedBottomLeftY = yRotatePixel(radians, -centerX, centerY);

	int yValues[4] = {rotatedBottomLeftY, rotatedBottomRightY, rotatedTopLeftY, rotatedTopRightY};
	
	int yMax = *max_element(yValues, yValues + 4);
	int yMin = *min_element(yValues, yValues + 4);

	return yMax - yMin;
}

void Image::superImpose(Image imageToImpose){

	//Caso feliz:
	//Una imagen es mas grande que la otra por superfice, ya que siempre son cuadradas.
	//Si se da el caso de que la nueva es mas grande que la actual, hago un resize de la nueva y se la 
	//asigno pixel a pixel a la vieja.


	int anchoImagen,altoImagen,altoPantalla,anchoPantalla,inicioAnchoPantalla,inicioAltoPantalla;
	
	anchoImagen=altoImagen=altoPantalla=anchoPantalla=0;
	
	anchoPantalla=this->getWidth();
	altoPantalla=this->getHeight();

	altoImagen=imageToImpose.getHeight();
	anchoImagen=imageToImpose.getWidth();


	long areaToImpose=altoImagen * anchoImagen;
	long currentImageArea= anchoPantalla * altoPantalla;

	if (areaToImpose > currentImageArea){
		//resize de la imagen a transparentar en caso de que sea mayor en area que la actual.
		imageToImpose.resize(this->getWidth(), this->getHeight());
		this->copy(imageToImpose);
	}
	else{

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
					Image::putPixel(pixelAImponer, i, j);

				}
			}
		}

	}

	return;


}