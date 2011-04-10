#include "StdAfx.h"
#include "Bonus.h"
#include "Logger.h"
#include <sstream>
using namespace std;

Bonus::Bonus(void) : tieneError(false)
{
	this->populateValidAttributes();
}

Bonus::Bonus(XmlElement e) : tieneError(false)
{
	this->populateValidAttributes();
	bool tieneError = this->validateAttributes(e);
	if (e.hasAttribute("tipo"))
	{
		tipo = e.getValue("tipo");
	}	
}

bool Bonus::validateAttributes(XmlElement& e)
{
	List<XmlAttribute> attributes = e.getAttributes();
	size_t len = attributes.length();

	for (size_t i = 0; i < len; i++)
	{
		XmlAttribute att = attributes[i];
		if (!this->validAttributes.contains(att.getKey()))
		{
			stringstream msg;
			msg << "Clave de atributo: " << att.getKey() << " no es válida para el Bonus. Linea: " << e.getStartLine();
			Logger::getInstance()->logError(msg.str());
			return false;
		}
	}

	return true;
}

Bonus::Bonus(std::string t)
{
	tipo = t;
}

std::string Bonus::getTipo()
{
	return tipo;
}

void Bonus::setTipoBonus(TipoBonus tb)
{
	tipoBonus = tb;
}

TipoBonus Bonus::getTipoBonus()
{
	return tipoBonus;
}

void Bonus::populateValidAttributes(void)
{
	this->validAttributes.add("tipo");
}

bool Bonus::hasError(void)
{
	return this->tieneError;
}

Bonus::~Bonus(void)
{
}