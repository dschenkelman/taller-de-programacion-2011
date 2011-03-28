#include "StdAfx.h"
#include "Celda.h"
#include <exception>

Celda::Celda(int f, int c)
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
