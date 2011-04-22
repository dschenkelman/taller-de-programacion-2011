#pragma once
#include "List.h"
#include "XmlElement.h"
#include "Celda.h"
#include "TipoObstaculo.h"
#include "TipoBonus.h"
#include "Logger.h"
#include "CellMatrix.h"
#include "TipoBonus.h"
#include "Textura.h"

const int defGridAncho = 10;
const int defGridAlto = 10;
const int defFila = 5;
const int defColumna = 5;

class Grilla
{
	bool tieneError;
	bool matrizGenerada;
	int ancho;
	int alto;
	std::string tipoObstaculoPorDefecto;
	List<List<Celda*>> matriz;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement& e);
	List<std::string> validAttributes;
	void generarMatriz(List<XmlElement>& le);
	bool colocarCeldaEnMatriz(Celda* c, int linea);
	bool verificarTipoBonusExistente(std::string tb);
	bool verificarTipoObstaculoExistente(std::string to);
	void verificarTiposUtilizados();
	TipoBonus obtenerTipoBonus(std::string tb);
	TipoObstaculo obtenerTipoObstaculo(std::string to);
	List<TipoObstaculo> tiposObstaculos;
	List<TipoBonus> tiposBonus;
public:
	Grilla(XmlElement& e, List<TipoObstaculo>& to, List<TipoBonus>& tb);
	Grilla(int an, int al, std::string& topd);
	Grilla(void);
	Grilla(const Grilla& other);
	Grilla& operator=(const Grilla& other);
	int getAncho();
	int getAlto();
	std::string getTipoObstaculoPorDefecto();
	Celda* getCelda(int fila, int columna);
	bool hasError(void);
	~Grilla(void);
};
