#pragma once
#include "Celda.h"
#include "XmlElement.h"
#include "TipoObstaculo.h"
#include "Image.h"
#include "Textura.h"

class Obstaculo : public Celda
{
	std::string tipo;
	TipoObstaculo tipoObstaculo;
	List<std::string> validAttributes;
	bool tieneError;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement& e);
	Image * imagen;
public:
	Obstaculo(std::string& tipo, int f, int c);
	Obstaculo(XmlElement& e);
	std::string getTipo();
	void setTipo(std::string t);
	void setTipoObstaculo(TipoObstaculo to);
	TipoObstaculo getTipoObstaculo();
	Celda* copiar(void);
	bool hasError(void);
	void setError(void);
	Textura obtenerTextura(Celda* celSup, Celda* celInf, Celda* celDer, Celda* celIzq);
	~Obstaculo(void);
	Image* obtenerRepresentacion(Celda* celSup, Celda* celInf, Celda* celDer, Celda* celIzq);
};
