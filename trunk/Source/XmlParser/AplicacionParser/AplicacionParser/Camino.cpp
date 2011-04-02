#include "StdAfx.h"
#include "Camino.h"
#include "List.h"

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
			throw std::exception();
		}

		fila = f;
	}

	if(e.hasAttribute("columna"))
	{
		std::string columnaString = e.getValue("columna");
		int c = atoi(columnaString.c_str());

		if (c < 0)
		{
			throw std::exception();
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
			//un camino con más de un bonus, por ahi hay que meter advertencia y usar un solo bonus
			throw std::exception();
		}
	}
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
