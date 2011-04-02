#pragma once
#include "List.h"
#include "XmlElement.h"
#include "Celda.h"
#include "TipoObstaculo.h"
#include "TipoBonus.h"
#include "Logger.h"

const int defGridAncho = 10;
const int defGridAlto = 10;

class Grilla
{
	int ancho;
	int alto;
	std::string tipoObstaculoPorDefecto;
	List<List<Celda>> matriz;
	void generarMatriz(List<XmlElement>& le);
	bool colocarCeldaEnMatriz(Celda& c);
	bool verificarTipoBonusExistente(std::string tb);
	bool verificarTipoObstaculoExistente(std::string to);
	List<TipoObstaculo> tiposObstaculos;
	List<TipoBonus> tiposBonus;
public:
	Grilla(XmlElement& e, List<TipoObstaculo>& to, List<TipoBonus>& tb);
	Grilla(int an, int al, std::string& topd);
	int getAncho();
	int getAlto();
	std::string getTipoObstaculoPorDefecto();
	List<List<Celda>> getMatriz();
	~Grilla(void);
};
