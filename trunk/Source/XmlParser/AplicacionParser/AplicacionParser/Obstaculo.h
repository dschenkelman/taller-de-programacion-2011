#pragma once
#include "Celda.h"
#include "XmlElement.h"

class Obstaculo : Celda
{
	std::string tipo;
public:
	Obstaculo(std::string tipo, size_t f, size_t c);
	Obstaculo(XmlElement e);
	std::string getTipo();
	~Obstaculo(void);
};
