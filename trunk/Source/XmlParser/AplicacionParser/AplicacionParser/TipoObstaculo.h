#pragma once
#include "XmlElement.h"

class TipoObstaculo
{
	std::string nombre;
	char textura;
	bool utilizado;
public:
	TipoObstaculo(XmlElement& e);
	TipoObstaculo(std::string& n, char t);
	TipoObstaculo(void);
	void utilizarTipo();
	bool esUtilizado();
	std::string getNombre();
	char getTextura();
	~TipoObstaculo(void);
};
