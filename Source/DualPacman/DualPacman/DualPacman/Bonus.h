#pragma once
#include "TipoBonus.h"
#include "Image.h"

class Bonus
{
	bool tieneError;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement& e);
	List<std::string> validAttributes;
	std::string tipo;
	TipoBonus tipoBonus;
	Image *imagen;
public:
	Bonus(void);
	Bonus(XmlElement& e);
	Bonus(std::string tipo);
	std::string getTipo();
	void setTipoBonus(TipoBonus tb);
	TipoBonus getTipoBonus();
	Image* obtenerRepresentacion(void);
	bool hasError(void);
	~Bonus(void);
};
