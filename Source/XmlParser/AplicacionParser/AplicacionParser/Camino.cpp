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

	/*List<XmlElement> listaHijos = e.getChildren();

	for(int i = 0; i < listaHijos.length(); i++)
	{
		if (listaHijos[i].hasAttribute("tipo"))
		{
			Bonus b(listaHijos[i]);
			bonus = b;
		}
	}*/
}

Bonus Camino::getBonus()
{
	return bonus;
}

Camino::~Camino(void)
{
}
