#pragma once
#include "Celda.h"
#include "Bonus.h"
#include "Logger.h"
#include <string>


class Camino : public Celda
{
	List<std::string> validAttributes;
	bool tieneError;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement& e);
	Bonus bonus;
	bool tieneBonus;
public:
	Camino(XmlElement& e);
	Camino(int f, int c);
	Camino(void);
	Bonus& getBonus();
	bool hasBonus();
	Celda* copiar(void);
	bool hasError(void);
	~Camino(void);
	Textura obtenerRepresentacion(Celda* celSup, Celda* celInf, Celda* celDer, Celda* celIzq);
};
