#pragma once
#include "Escenario.h"
#include <map>
#include <string>
#include "Image.h"

class Grapher
{
private:
	int windowHeight;
	int windowWidth;
	int imageHeight;
	int imageWidth;
	std::map<std::string, Image *> imageCache;  
	std::map<std::string, Image *>::iterator iter;
	bool error;
public:
	Image* draw(Escenario& escenario);
	void setVideoMode(int mode);
	int getVideoMode(void);
	bool hasError();
	int getImageHeight();
	int getImageWidth();
	Grapher();
	~Grapher();
};