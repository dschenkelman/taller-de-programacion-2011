#pragma once
#include "List.h"
#include "XmlElement.h"
#include "Celda.h"

class Grilla
{
	int ancho;
	int alto;
	std::string tipoObstaculoPorDefecto;
	List<List<Celda>> matriz;
	bool generarMatriz(List<XmlElement> le);
public:
	Grilla(XmlElement e);
	Grilla(int an, int al, std::string topd);
	int getAncho();
	int getAlto();
	std::string getTipoObstaculoPorDefecto();
	List<List<Celda>> getMatriz();
	~Grilla(void);
};
