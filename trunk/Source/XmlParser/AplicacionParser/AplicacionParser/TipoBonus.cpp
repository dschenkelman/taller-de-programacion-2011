#include "StdAfx.h"
#include "TipoBonus.h"
#include "Logger.h"
#include <sstream>

TipoBonus::TipoBonus(void)
{
}

TipoBonus::TipoBonus(std::string& n, char t)
{
	nombre = n;
	textura = t;
}

TipoBonus::TipoBonus(XmlElement& e)
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
			// Loggeo una advertencia por tener una textura de mas de un caracter
			std::stringstream nroLinea;	nroLinea << e.getStartLine();
			Logger::getInstance()->logWarning("Línea " + nroLinea.str() + " -> En TipoObstaculo, la textura tiene mas de un caracter.");
		}

		textura = t.at(0);
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
