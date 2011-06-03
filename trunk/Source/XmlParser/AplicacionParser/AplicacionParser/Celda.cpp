#include "StdAfx.h"
#include "Celda.h"
#include <exception>
#include "Logger.h"
#include "Image.h"


Celda::Celda(int f, int c) : ocupada(false)
{
	if(f < 0 || c < 0)
	{
		Logger::getInstance()->logError("En entidad Celda, fila o columna menor a cero.");
		throw std::exception();
	}
	fila = f;
	columna = c;
}

Celda::Celda(void) : ocupada(false), fila(0), columna(0)
{
}

bool Celda::esOcupada()
{
	return ocupada;
}

void Celda::Ocupar()
{
	ocupada = true;
}

int Celda::getColumna()
{
	return columna;
}

int Celda::getFila()
{
	return fila;
}

Celda::~Celda(void)
{
}


Image* Celda::obtenerRepresentacion()
{
	// Esto no se debería imprimir nunca
	return new Image(0,0);
}

Celda* Celda::copiar(void)
{
	Celda* celda = new Celda(this->fila, this->columna);
	celda->ocupada = this->ocupada;
	return celda;
}
bool Celda::hasError(void)
{
	return false;
}

Textura Celda::obtenerTextura()
{
	return Textura();
}

void Celda::setearRepresentacion(Image* rep)
{
}