#pragma once
#include "XmlElement.h"
#include <string>

class TipoObstaculo
{
	int numeroLinea;
	std::string nombre;
	List<std::string> validAttributes;
	bool tieneError;
	std::string textura;
	bool utilizado;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement& e);
public:
	TipoObstaculo(XmlElement& e);
	TipoObstaculo(std::string& n, std::string& t);
	TipoObstaculo(void);
	void utilizarTipo();
	bool esUtilizado();
	std::string getNombre();
	bool hasError(void);
	std::string getTextura();
	int getLinea(void);
	void setLinea(int);
	~TipoObstaculo(void);
};
