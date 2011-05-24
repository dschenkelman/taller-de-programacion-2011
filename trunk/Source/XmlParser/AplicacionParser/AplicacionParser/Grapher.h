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
	std::map<std::string, Image *> imageCache;  
	std::map<std::string, Image *>::iterator iter;

public:
	void draw(Escenario& escenario);
	void setVideoMode(int mode);
	int getVideoMode(void);
	Grapher();
	~Grapher();
};