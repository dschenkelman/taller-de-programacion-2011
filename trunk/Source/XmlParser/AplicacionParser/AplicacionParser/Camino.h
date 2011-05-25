#pragma once
#include "Celda.h"
#include "Bonus.h"
#include "Logger.h"
#include <string>
#include "Image.h"

class Camino : public Celda
{
	List<std::string> validAttributes;
	bool tieneError;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement& e);
	Bonus bonus;
	bool tieneBonus;
	Image * imagen;
public:
	Camino(XmlElement& e);
	Camino(int f, int c);
	Camino(void);
	Bonus& getBonus();
	bool hasBonus();
	Celda* copiar(void);
	bool hasError(void);
	~Camino(void);
	Textura obtenerTextura(Celda* celSup, Celda* celInf, Celda* celDer, Celda* celIzq);
	Image* obtenerRepresentacion(Celda* celSup, Celda* celInf, Celda* celDer, Celda* celIzq);
};
