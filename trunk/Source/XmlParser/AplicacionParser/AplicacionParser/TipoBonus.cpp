#include "StdAfx.h"
#include "TipoBonus.h"

TipoBonus::TipoBonus(std::string n, char t)
{
	nombre = n;
	textura = t;
}

TipoBonus::TipoBonus(XmlElement e)
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

std::string TipoBonus::getNombre(void)
{
	return nombre;
}

char TipoBonus::getTextura(void)
{
	return textura;
}

TipoBonus::~TipoBonus(void)
{
}
