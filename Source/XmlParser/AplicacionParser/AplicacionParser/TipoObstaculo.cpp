#include "StdAfx.h"
#include "TipoObstaculo.h"
#include "Logger.h"
#include <sstream>

TipoObstaculo::TipoObstaculo(XmlElement& e)
{
	utilizado = false;

	if(e.hasAttribute("nombre"))
	{
		nombre = e.getValue("nombre");
	}

	if(e.hasAttribute("textura"))
	{
		std::string t = e.getValue("textura");

		if(t.length() != 1)
		{
			// Loggeo como warning que la textura tenga mas de un caracter
			std::stringstream nroLinea;	nroLinea << e.getStartLine();
			Logger::getInstance()->logError("Línea " + nroLinea.str() + " -> En TipoObstaculo, textura con mas de un caracter.");
		}

		textura = t.at(0);
	}
}

TipoObstaculo::TipoObstaculo(void)
{
	utilizado = false;
}

TipoObstaculo::TipoObstaculo(std::string& n, char t)
{
	nombre = n;
	textura = t;
	utilizado = false;
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

void TipoObstaculo::utilizarTipo()
{
	utilizado = true;
}

bool TipoObstaculo::esUtilizado()
{
	return utilizado;
}