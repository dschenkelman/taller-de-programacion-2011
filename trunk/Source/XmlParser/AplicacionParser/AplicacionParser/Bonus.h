#pragma once
#include "TipoBonus.h"
#include "Image.h"

class Bonus
{
	Bonus( const Bonus& b );
	Bonus& operator=( const Bonus& b );
	bool tieneError;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement& e);
	List<std::string> validAttributes;
	std::string tipo;
	TipoBonus tipoBonus;
	double frecuencia;
	int duracion;
public:
	Bonus(void);
	Bonus(XmlElement& e);
	Bonus(std::string tipo);
	std::string getTipo();
	void setTipoBonus(TipoBonus& tb);
	TipoBonus& getTipoBonus();
	Image* obtenerRepresentacion(void);
	bool hasError(void);
	~Bonus(void);
};
