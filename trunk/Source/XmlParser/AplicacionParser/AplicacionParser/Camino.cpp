#include "StdAfx.h"
#include "Camino.h"
#include "List.h"

Camino::Camino(size_t f, size_t c)
{
	fila = f;
	columna = c;
}

Camino::Camino(XmlElement e)
{
	if (e.hasAttribute("fila") && e.hasAttribute("columna"))
	{
		//fila = e.getValue("fila");
		//columna = e.getValue("columna");
	}

	/*List<XmlElement> listaHijos = e.getChildren();
	
	for(size_t i = 0; i < listaHijos.length(); i++)
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
