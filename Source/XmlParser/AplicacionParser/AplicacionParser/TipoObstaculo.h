#pragma once
#include "XmlElement.h"
#include "List.h"
#include <string>
#include "Textura.h"

class TipoObstaculo
{
	int numeroLinea;
	std::string nombre;
	List<std::string> validAttributes;
	bool tieneError;
	std::string nombreTextura;
	Textura textura;
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
	std::string getNombreTextura();
	void setTextura(Textura&);
	int getLinea(void);
	void setLinea(int);
	~TipoObstaculo(void);
};
