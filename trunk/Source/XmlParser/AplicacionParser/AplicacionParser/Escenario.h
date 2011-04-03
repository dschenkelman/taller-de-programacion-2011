#pragma once
#include "Grilla.h"
#include "TipoBonus.h"
#include "List.h"
#include "TipoObstaculo.h"
#include "XmlElement.h"

class Escenario
{
	std::string nombre;
	Grilla grilla;
	List<TipoBonus> tiposBonus;
	List<TipoObstaculo> tiposObstaculos;
	List<TipoBonus> obtenerTiposBonus(List<XmlElement>& le);
	List<TipoObstaculo> obtenerTiposObstaculos(List<XmlElement>& le);
public:
	Escenario(void);
	Escenario(XmlElement& e);
	List<TipoBonus> getTiposBonus(void);
	List<TipoObstaculo> getTiposObstaculos(void);
	Grilla getGrilla(void);
	std::string getNombre(void);
	~Escenario(void);
};
