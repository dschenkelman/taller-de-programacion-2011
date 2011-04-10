#pragma once
#include "XmlElement.h"
#include <string>

class TipoObstaculo
{
	std::string nombre;
	List<std::string> validAttributes;
	bool tieneError;
	char textura;
	bool utilizado;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement& e);
public:
	TipoObstaculo(XmlElement& e);
	TipoObstaculo(std::string& n, char t);
	TipoObstaculo(void);
	void utilizarTipo();
	bool esUtilizado();
	std::string getNombre();
	bool hasError(void);
	char getTextura();
	~TipoObstaculo(void);
};
