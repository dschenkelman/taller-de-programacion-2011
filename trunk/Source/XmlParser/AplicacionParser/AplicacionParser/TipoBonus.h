#pragma once
#include "XmlElement.h"

class TipoBonus
{
	std::string nombre;
	char textura;
	bool utilizado;
public:
	TipoBonus(XmlElement& e);
	TipoBonus(std::string& n, char t);
	TipoBonus(void);
	void utilizarTipo();
	bool esUtilizado();
	std::string getNombre(void);
	char getTextura(void);
	~TipoBonus(void);

};
