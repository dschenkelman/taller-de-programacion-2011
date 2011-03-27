#include "StdAfx.h"
#include "Celda.h"
#include <exception>

Celda::Celda(size_t f, size_t c)
{
	if(f < 0 || c < 0)
	{
		throw std::exception();
	}
	fila = f;
	columna = c;
}

Celda::Celda(void)
{
}

size_t Celda::getColumna()
{
	return columna;
}

size_t Celda::getFila()
{
	return fila;
}

Celda::~Celda(void)
{
}
