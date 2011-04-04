#pragma once
#include "stdafx.h"
#include <string>
#include "celda.h"

class Obstaculo: public Celda{
private:
	std::string nombre;
public:
	Obstaculo(void);
	~Obstaculo(void);
	std::string getNombre(void);
	void setNombre(std::string nombre);
	std::string obtenerRepresentacion(void);
};