#include "StdAfx.h"
#include "Obstaculo.h"
#include "Logger.h"
#include <sstream>

Obstaculo::Obstaculo(std::string& t, int f, int c) : Celda(f, c)
{
	this->tipo = t;
}

Obstaculo::Obstaculo(XmlElement& e)
{
	if (e.hasAttribute("tipo"))
	{
		tipo = e.getValue("tipo");
	}

	else
	{
		tipo = "";
	}

	if (e.hasAttribute("fila"))
	{
		std::string filaString = e.getValue("fila");
		int f = atoi(filaString.c_str());

		if(f < 0)
		{
			// Loggeo como Error que la fila sea menor a cero
			std::stringstream nroLinea;	nroLinea << e.getStartLine();
			Logger::getInstance()->logError("Línea " + nroLinea.str() + " -> En Obstaculo, fila menor a cero.");
		}

		fila = f;
	}

	if(e.hasAttribute("columna"))
	{
		std::string columnaString = e.getValue("columna");
		int c = atoi(columnaString.c_str());

		if (c < 0)
		{
			// Loggeo como Error que la fila sea menor a cero
			std::stringstream nroLinea;	nroLinea << e.getStartLine();
			Logger::getInstance()->logError("Línea " + nroLinea.str() + " -> En Obstaculo, columna menor a cero.");
		}

		columna = c;
	}
}

std::string Obstaculo::getTipo()
{
	return tipo;
}

void Obstaculo::setTipo(std::string t)
{
	tipo = t;
}

void Obstaculo::setTipoObstaculo(TipoObstaculo to)
{
	tipoObstaculo = to;
}

TipoObstaculo Obstaculo::getTipoObstaculo()
{
	return tipoObstaculo;
}

Obstaculo::~Obstaculo(void)
{
}

std::string Obstaculo::obtenerRepresentacion(Celda* celSup, Celda* celInf, Celda* celDer, Celda* celIzq)
{
	return ""+this->getTipoObstaculo().getTextura();
}

Celda* Obstaculo::copiar(void)
{
	Obstaculo* obstaculo = new Obstaculo(this->tipo, this->fila, this->columna);
	obstaculo->ocupada = this->ocupada;
	obstaculo->tipoObstaculo = this->tipoObstaculo;
	return obstaculo;
}