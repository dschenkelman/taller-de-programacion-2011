#include "StdAfx.h"
#include "TipoBonus.h"
#include "Logger.h"
#include <sstream>

using namespace std;

TipoBonus::TipoBonus(void) : tieneError(false), utilizado(false)
{
	this->populateValidAttributes();
}

TipoBonus::TipoBonus(std::string& n, char t) : tieneError(false), utilizado(false), nombre(n), textura(t)
{
	this->populateValidAttributes();
}

TipoBonus::TipoBonus(XmlElement& e) : tieneError(false), utilizado(false)
{
	this->populateValidAttributes();
	this->tieneError = !this->validateAttributes(e);
	
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

void TipoBonus::utilizarTipo()
{
	utilizado = true;
}

bool TipoBonus::hasError(void)
{
	return this->tieneError;
}

TipoBonus::~TipoBonus(void)
{
}

bool TipoBonus::esUtilizado()
{
	return utilizado;
}

bool TipoBonus::validateAttributes(XmlElement& e)
{
	List<XmlAttribute> attributes = e.getAttributes();
	size_t len = attributes.length();

	for (size_t i = 0; i < len; i++)
	{
		XmlAttribute att = attributes[i];
		if (!this->validAttributes.contains(att.getKey()))
		{
			stringstream msg;
			msg << "Clave de atributo: " << att.getKey() << " no es válida para el TipoBonus. Linea: " << e.getStartLine();
			Logger::getInstance()->logError(msg.str());
			return false;
		}
	}

	return true;
}

void TipoBonus::populateValidAttributes(void)
{
	this->validAttributes.add("nombre");
	this->validAttributes.add("textura");
}

void TipoBonus::setLinea(int l)
{
	this->numeroLinea = l;
}

int TipoBonus::getLinea(void)
{
	return this->numeroLinea;
}