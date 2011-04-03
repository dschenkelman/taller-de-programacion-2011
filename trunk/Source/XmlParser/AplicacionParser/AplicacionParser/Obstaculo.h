#pragma once
#include "Celda.h"
#include "XmlElement.h"

class Obstaculo : public Celda
{
	std::string tipo;
public:
	Obstaculo(std::string& tipo, int f, int c);
	Obstaculo(XmlElement& e);
	std::string getTipo();
	void setTipo(std::string t);
	~Obstaculo(void);
	std::string obtenerRepresentacion(void);
};
