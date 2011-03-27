#include "StdAfx.h"
#include "TipoObstaculo.h"

TipoObstaculo::TipoObstaculo(XmlElement e)
{
	if(e.hasAttribute("nombre") && e.hasAttribute("textura"))
	{
		nombre = e.getValue("nombre");
		std::string t = e.getValue("textura");

		if(t.length() == 1)
		{
			textura = t.at(0);
		}
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
