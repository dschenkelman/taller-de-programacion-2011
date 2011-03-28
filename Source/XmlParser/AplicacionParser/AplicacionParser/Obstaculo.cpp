#include "StdAfx.h"
#include "Obstaculo.h"

Obstaculo::Obstaculo(std::string t, int f, int c)
{
	tipo = t;
	fila = f;
	columna = c;
}

Obstaculo::Obstaculo(XmlElement e)
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
}

std::string Obstaculo::getTipo()
{
	return tipo;
}

Obstaculo::~Obstaculo(void)
{
}
