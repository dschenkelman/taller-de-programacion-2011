#pragma once
# include "XmlElement.h"

class TipoBonus
{
	std::string nombre;
	char textura;
public:
	TipoBonus(XmlElement e);
	TipoBonus(std::string n, char t);
	std::string getNombre(void);
	char getTextura(void);
	~TipoBonus(void);

};
