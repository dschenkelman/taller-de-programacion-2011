#pragma once
#include "Celda.h"
#include "XmlElement.h"
#include "TipoObstaculo.h"

class Obstaculo : public Celda
{
	std::string tipo;
	TipoObstaculo tipoObstaculo;
	List<std::string> validAttributes;
	bool tieneError;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement& e);
public:
	Obstaculo(std::string& tipo, int f, int c);
	Obstaculo(XmlElement& e);
	std::string getTipo();
	void setTipo(std::string t);
	void setTipoObstaculo(TipoObstaculo to);
	TipoObstaculo getTipoObstaculo();
	Celda* copiar(void);
	bool hasError(void);
	~Obstaculo(void);
	std::string obtenerRepresentacion(Celda* celSup, Celda* celInf, Celda* celDer, Celda* celIzq);
};
