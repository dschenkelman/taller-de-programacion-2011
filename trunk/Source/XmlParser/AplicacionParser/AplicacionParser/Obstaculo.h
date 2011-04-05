#pragma once
#include "Celda.h"
#include "XmlElement.h"
#include "TipoObstaculo.h"

class Obstaculo : public Celda
{
	std::string tipo;
	TipoObstaculo tipoObstaculo;
public:
	Obstaculo(std::string& tipo, int f, int c);
	Obstaculo(XmlElement& e);
	std::string getTipo();
	void setTipo(std::string t);
	void setTipoObstaculo(TipoObstaculo to);
	TipoObstaculo getTipoObstaculo();
	~Obstaculo(void);
	std::string obtenerRepresentacion(Celda* celSup, Celda* celInf, Celda* celDer, Celda* celIzq);
};
