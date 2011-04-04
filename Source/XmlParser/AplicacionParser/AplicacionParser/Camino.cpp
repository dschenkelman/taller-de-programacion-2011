#include "StdAfx.h"
#include "Camino.h"
#include "List.h"
#include <sstream>

Camino::Camino(int f, int c)
{
	fila = f;
	columna = c;
}

Camino::Camino(XmlElement& e)
{
	if (e.hasAttribute("fila"))
	{
		std::string filaString = e.getValue("fila"); 
		int f = atoi(filaString.c_str());

		if (f < 0)
		{
			// Loggeo como Error que la fila sea menor a cero
			std::stringstream nroLinea;	nroLinea << e.getStartLine();
			Logger::getInstance()->logError("L�nea " + nroLinea.str() + " -> En Camino, fila menor a cero.");
		}

		fila = f;
	}

	if(e.hasAttribute("columna"))
	{
		std::string columnaString = e.getValue("columna");
		int c = atoi(columnaString.c_str());

		if (c < 0)
		{
			// Loggeo como Error que la columna sea menor a cero
			std::stringstream nroLinea;	nroLinea << e.getStartLine();
			Logger::getInstance()->logError("L�nea " + nroLinea.str() + " -> En Camino, columna menor a cero.");
		}

		columna = c;
	}

	tieneBonus = false;

	if (e.hasChildren())
	{
		List<XmlElement> listaHijos = e.getChildren();
		
		if(listaHijos.length() == 1)
		{
			Bonus b = Bonus(listaHijos.at(0));
			bonus = b;
			tieneBonus = true;
		}

		else
		{
			//un camino con m�s de un bonus, por ahi hay que meter advertencia y usar un solo bonus
			std::stringstream nroLinea;	nroLinea << e.getStartLine();
			Logger::getInstance()->logWarning("L�nea "+nroLinea.str()+" -> En Camino, la cantidad de bonus es mayor a uno.");
		}
	}
}

Camino::Camino(void)
{
}

bool Camino::hasBonus()
{
	return tieneBonus;
}

Bonus Camino::getBonus()
{
	return bonus;
}

Camino::~Camino(void)
{
}

std::string Camino::obtenerRepresentacion(void)
{
	std::string representacion = "c";
	
	if (this->hasBonus())
	{
		representacion = this->bonus.getTipoBonus().getTextura();
	}

	return representacion;
}