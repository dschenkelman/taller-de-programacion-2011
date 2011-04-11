#pragma once
#include "Grilla.h"
#include "TipoBonus.h"
#include "List.h"
#include "TipoObstaculo.h"
#include "XmlElement.h"
#include "Logger.h"

class Escenario
{
	std::string nombre;
	Grilla grilla;
	bool tieneError;
	List<std::string> validAttributes;
	List<TipoBonus> tiposBonus;
	List<TipoObstaculo> tiposObstaculos;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement& e);
	List<TipoBonus> obtenerTiposBonus(List<XmlElement>& le);
	List<TipoObstaculo> obtenerTiposObstaculos(List<XmlElement>& le);
	bool verificarTexturaEnLista(List<char>& listaCaracteres, char t);
public:
	Escenario(void);
	Escenario(XmlElement& e);
	List<TipoBonus> getTiposBonus(void);
	List<TipoObstaculo> getTiposObstaculos(void);
	Grilla& getGrilla(void);
	std::string getNombre(void);
	bool hasError(void);
	~Escenario(void);
};
