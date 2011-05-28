#pragma once
#include <string>
#include "sdl/sdl.h"
#include "Image.h"
#include "Activity.h"

class Window
{
	bool closed;
	int height;
	int width;
	SDL_Surface* window;	
	std::string title;
	Uint32 getPixel(int x, int y) const;
	void putPixel(Uint32 pixel, int x, int y);
	void putPixel(SDL_Surface *surface, Uint32 pixel, int x, int y);
private:
	Activity* currentActivity;

public:
	Window(std::string, int h, int w);
	void close(void);
	void refresh(void);
	void display(Image* image, int x, int y, int red, int blue, int green, int delta);
	~Window(void);
	void init();
	void setCurrentActivity(Activity* ac);
	Activity* getCurrentActivity();
		int getHeight(void)
	{
		return this->height;
	}
	int getWidth(void)
	{
		return this->width;
	}
};
