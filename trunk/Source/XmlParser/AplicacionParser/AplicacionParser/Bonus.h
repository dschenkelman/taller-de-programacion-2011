#pragma once
#include "TipoBonus.h"

class Bonus
{
	bool tieneError;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement& e);
	List<std::string> validAttributes;
	std::string tipo;
	TipoBonus tipoBonus;
public:
	Bonus(void);
	Bonus(XmlElement& e);
	Bonus(std::string tipo);
	std::string getTipo();
	void setTipoBonus(TipoBonus tb);
	TipoBonus getTipoBonus();
	bool hasError(void);
	~Bonus(void);
};
