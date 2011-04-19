#pragma once
#include "XmlElement.h"
#include <string>

class Textura
{
	bool tieneError;
	List<std::string> validAttributes;
	std::string nombre;
	std::string archivo;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement& e);
public:
	Textura(void);
	Textura(XmlElement& element);
	std::string getNombre(void);
	std::string getArchivo(void);
	bool hasError(void);
	~Textura(void);
};
