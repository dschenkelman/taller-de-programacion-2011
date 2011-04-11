#include "StdAfx.h"
#include "Celda.h"
#include <exception>
#include "Logger.h"


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


std::string Celda::obtenerRepresentacion(Celda* celSup, Celda* celInf, Celda* celDer, Celda* celIzq)
{
	// Esto no se debería imprimir nunca
	return "?";
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
