#pragma once
#include <string>
#include "Image.h"
#include "Textura.h"
#include "Image.h"

class Celda
{
	Celda( const Celda& c );
	Celda& operator=( const Celda& c );
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
	virtual Image* obtenerRepresentacion();
	virtual void setearRepresentacion(Image*);
	virtual Textura obtenerTextura();
	virtual bool hasError(void);
};
