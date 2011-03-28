#pragma once
#include "TipoBonus.h"

class Bonus
{
	std::string tipo;
	TipoBonus tipoBonus;
public:
	Bonus(void);
	Bonus(XmlElement e);
	Bonus(std::string tipo);
	std::string getTipo();
	void setTipoBonus(TipoBonus tb);
	TipoBonus getTipoBonus();
	~Bonus(void);
};
