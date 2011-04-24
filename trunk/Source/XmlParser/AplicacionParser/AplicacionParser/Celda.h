#pragma once
#include <string>
#include "Textura.h"

class Celda
{
protected:
	int fila;
	int columna;
	bool ocupada;
public:
	Celda(int f, int c);
	Celda(void);
	int getFila();
	int getColumna();
	bool esOcupada();
	void Ocupar();
	virtual Celda* copiar(void);
	virtual ~Celda(void);
	virtual Textura obtenerRepresentacion(Celda* celSup, Celda* celInf, Celda* celDer, Celda* celIzq);
	virtual bool hasError(void);
};
