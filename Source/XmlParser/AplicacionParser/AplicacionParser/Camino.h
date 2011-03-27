#pragma once
#include "Celda.h"
#include "Bonus.h"

class Camino : Celda
{
	Bonus bonus;
public:
	Camino(XmlElement e);
	Camino(size_t f, size_t c);
	Bonus getBonus();
	~Camino(void);
};
