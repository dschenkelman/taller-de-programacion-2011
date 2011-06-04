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
	Bonus* bonus;
	bool tieneBonus;
	Image* imagen;
	Camino(const Camino& other);
	Camino& operator=(const Camino& other);
public:
	Camino(XmlElement& e);
	Camino(int f, int c);
	Camino(void);
	Bonus* getBonus();
	bool hasBonus();
	void removeBonus(void);
	Celda* copiar(void);
	bool hasError(void);
	virtual ~Camino(void);
	Textura obtenerTextura();
	Image* obtenerRepresentacion();
	void setearRepresentacion(Image*);
};
