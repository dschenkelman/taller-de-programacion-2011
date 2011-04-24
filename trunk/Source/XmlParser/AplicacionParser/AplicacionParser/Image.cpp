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
    Uint8 *p = (Uint8 *)this->image->pixels + y * this->image->pitch + x * bpp;

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
	return (cos(radians) * x - sin(radians) * y);
}

int Image::yRotatePixel(double radians, int x, int y)
{
	return sin(radians) * x + cos(radians) * y;
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
	double radians = (degrees * PI) / 180;

	int rotatedHeight = this->getRotatedHeight(radians);
	int rotatedWidth = this->getRotatedWidth(radians);

	Image temp(rotatedWidth, rotatedHeight);

	int centerX = this->getWidth() / 2;		
	int centerY = this->getHeight() / 2;

	for (int i = 0; i < rotatedHeight; i++) 
	{
		for (int j = 0; j < rotatedWidth; j++) 
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
			temp.putPixel(pixelImg, rotatedX + newCenterX, rotatedY + newCenterY);
		}
	}
		
	this->copy(temp);
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