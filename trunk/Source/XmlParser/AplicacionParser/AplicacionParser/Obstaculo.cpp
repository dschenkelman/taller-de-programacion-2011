#include "StdAfx.h"
#include "Obstaculo.h"
#include "Logger.h"
#include <sstream>

Obstaculo::Obstaculo(std::string& t, int f, int c)
{
	tipo = t;
	fila = f;
	columna = c;
}

Obstaculo::Obstaculo(XmlElement& e)
{
	if (e.hasAttribute("tipo"))
	{
		tipo = e.getValue("tipo");
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

Obstaculo::~Obstaculo(void)
{
}
