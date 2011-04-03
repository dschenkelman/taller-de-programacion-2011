#pragma once
#include "Celda.h"
#include "Bonus.h"
#include "Logger.h"


class Camino : public Celda
{
	Bonus bonus;
	bool tieneBonus;
public:
	Camino(XmlElement& e);
	Camino(int f, int c);
	Camino(void);
	Bonus getBonus();
	bool hasBonus();
	~Camino(void);
};
