#include "StdAfx.h"
#include "TipoObstaculo.h"

TipoObstaculo::TipoObstaculo(XmlElement e)
{
	if(e.hasAttribute("nombre"))
	{
		nombre = e.getValue("nombre");
	}

	if(e.hasAttribute("textura"))
	{
		std::string t = e.getValue("textura");

		if(t.length() != 1)
		{
			throw std::exception();
		}

		textura = t.at(0);
	}
}

TipoObstaculo::TipoObstaculo(std::string n, char t)
{
	nombre = n;
	textura = t;
}

TipoObstaculo::~TipoObstaculo(void)
{
}

std::string TipoObstaculo::getNombre()
{
	return nombre;
}

char TipoObstaculo::getTextura()
{
	return textura;
}
