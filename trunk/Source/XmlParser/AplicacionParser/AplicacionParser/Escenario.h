#pragma once
#include "Grilla.h"
#include "TipoBonus.h"
#include "List.h"
#include "TipoObstaculo.h"
#include "XmlElement.h"
#include "Logger.h"
#include "Textura.h"

class Escenario
{
	std::string texturaFondo;
	std::string nombre;
	Grilla grilla;
	bool tieneError;
	List<std::string> validAttributes;
	List<TipoBonus> tiposBonus;
	List<TipoObstaculo> tiposObstaculos;
	List<Textura> texturas;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement& e);
	List<TipoBonus> obtenerTiposBonus(List<XmlElement>& le);
	List<TipoObstaculo> obtenerTiposObstaculos(List<XmlElement>& le);
	List<Textura> obtenerTexturas(List<XmlElement>& le);
	bool verificarTexturaEnLista(List<char>& listaCaracteres, char t);
	void getTexturaFondoFromElement(XmlElement&);
public:
	Escenario(void);
	Escenario(XmlElement& e);
	List<TipoBonus> getTiposBonus(void);
	List<TipoObstaculo> getTiposObstaculos(void);
	List<Textura> getTexturas(void);
	Grilla& getGrilla(void);
	std::string getNombre(void);
	std::string getTexturaFondo(void);
	bool hasError(void);
	~Escenario(void);
};
