#pragma once
#include "Celda.h"
#include "Bonus.h"


class Camino : public Celda
{
	Bonus bonus;
public:
	Camino(XmlElement e);
	Camino(int f, int c);
	Bonus getBonus();
	~Camino(void);
};
