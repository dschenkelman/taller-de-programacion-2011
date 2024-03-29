#pragma once
#include <string>
#include "sdl/sdl.h"
#include <limits>

class Image
{
	SDL_Surface* image;
	bool error;
	std::string errorMessage;
	int height;
	int width;
	static void putPixel(SDL_Surface* surface, Uint32 pixel, int x, int y);
	static double xRotatePixel(double radians, double x, double y);
	static double yRotatePixel(double radians, double x, double y);
	int getRotatedHeight(double radians);
	int getRotatedWidth(double radians);
	void resizeOnePixelImage();
	Uint32 getInterpolatedPixel(Uint32 pixelSI, double xSI, double ySI, Uint32 pixelSD, double xSD, double ySD, Uint32 pixelII, double xII, double yII, Uint32 pixelID, double xID, double yID, double xNow, double yNow, const SDL_PixelFormat* newFormat);
public:
	Image(std::string path);
	Image(void);
	Image(int width, int height); // Empty image constructor
	Image(const Image& other);
	Image& operator=(const Image& other);
	~Image(void);
	SDL_Surface* getSDLSurface(void) const;
	int getWidth(void) const;
	int getHeight(void) const;
	std::string getErrorMessage(void) const;
	bool hasError(void) const;
	bool validLimits(int x, int y);
	Uint32 getPixel(int x, int y) const;
	static Uint32 getPixel(SDL_Surface* surface, int x, int y);
	void crop(int top, int left, int right, int bottom);
	void resize(int newWidth, int newHeight);
	void putPixel(Uint32 pixel, int x, int y);
	void copy(const Image& other);
	const SDL_PixelFormat* getFormat() const;
	void rotate(int degrees, Uint32 alpha);
	void superImpose(Image& imageToImpose, int red, int green, int blue, int delta);
};
