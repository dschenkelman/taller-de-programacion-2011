#pragma once
#include "Escenario.h"

class Grapher
{
private:
	int windowHeight;
	int windowWidth;
public:
	void draw(Escenario& escenario);
	void setVideoMode(int mode);
	int getVideoMode(void);
	Grapher();
	~Grapher();
};