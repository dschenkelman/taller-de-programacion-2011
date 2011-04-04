#pragma once
#include "celda.h"

class Camino :
	public Celda
{
public:
	Camino(void);
	~Camino(void);
	std::string obtenerRepresentacion(void);
};
