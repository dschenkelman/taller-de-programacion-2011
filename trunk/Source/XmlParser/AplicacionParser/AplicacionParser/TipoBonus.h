#pragma once
#include "XmlElement.h"
#include "List.h"
#include <string>
#include "Textura.h"

class TipoBonus
{
	int numeroLinea;
	std::string nombre;
	List<std::string> validAttributes;
	std::string nombreTextura;
	Textura textura;
	bool utilizado;
	bool tieneError;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement& e);
	int duracion;
	int apariciones;
	int probabilidad;
	std::string unidad;
public:
	TipoBonus(XmlElement& e);
	TipoBonus(std::string& n, std::string& t);
	TipoBonus(void);
	void utilizarTipo();
	bool esUtilizado();
	std::string getNombre(void);
	bool hasError(void);
	std::string getNombreTextura(void);
	void setTextura(Textura&);
	Textura& getTextura(void);
	void setLinea(int);
	int getLinea(void);
	int getProbabilidad(void);
	int getApariciones();
	void decreaseApariciones();
	int getDuracion(void);
	std::string getUnidad(void);
	~TipoBonus(void);
};
