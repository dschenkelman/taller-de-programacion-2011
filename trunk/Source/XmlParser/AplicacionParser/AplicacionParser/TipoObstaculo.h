#pragma once
#include "XmlElement.h"

class TipoObstaculo
{
	std::string nombre;
	char textura;
public:
	TipoObstaculo(XmlElement& e);
	TipoObstaculo(std::string& n, char t);
	TipoObstaculo(void);
	std::string getNombre();
	char getTextura();
	~TipoObstaculo(void);
};
