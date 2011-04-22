#pragma once
#include "Escenario.h"

class Grapher
{
	static const int windowHeight = 480;
	static const int windowWidth = 640;
public:
	void draw(Escenario& escenario);
	Grapher();
	~Grapher();
};