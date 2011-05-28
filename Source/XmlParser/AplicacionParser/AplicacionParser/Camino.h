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
	Image* imagen;
public:
	Camino(XmlElement& e);
	Camino(int f, int c);
	Camino(void);
	Camino(const Camino& other);
	Camino& operator=(const Camino& other);
	Bonus& getBonus();
	bool hasBonus();
	void removeBonus(void);
	Celda* copiar(void);
	bool hasError(void);
	~Camino(void);
	Textura obtenerTextura();
	Image* obtenerRepresentacion();
	Image* borrarBonus();
};
