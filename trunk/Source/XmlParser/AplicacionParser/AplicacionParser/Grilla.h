#pragma once
#include "List.h"
#include "XmlElement.h"
#include "Celda.h"

class Grilla
{
	size_t ancho;
	size_t alto;
	std::string tipoObstaculoPorDefecto;
	List<List<Celda>> matriz;
	bool generarMatriz(List<XmlElement> le);
public:
	Grilla(XmlElement e);
	Grilla(size_t an, size_t al, std::string topd);
	size_t getAncho();
	size_t getAlto();
	std::string getTipoObstaculoPorDefecto();
	List<List<Celda>> getMatriz();
	~Grilla(void);
};
