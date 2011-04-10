#pragma once
#include "XmlElement.h"
#include "List.h"
#include <string>

class TipoBonus
{
	std::string nombre;
	List<std::string> validAttributes;
	char textura;
	bool utilizado;
	bool tieneError;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement& e);
public:
	TipoBonus(XmlElement& e);
	TipoBonus(std::string& n, char t);
	TipoBonus(void);
	void utilizarTipo();
	bool esUtilizado();
	std::string getNombre(void);
	bool hasError(void);
	char getTextura(void);
	~TipoBonus(void);

};
