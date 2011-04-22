#include "StdAfx.h"
#include "TipoBonus.h"
#include "Logger.h"
#include <sstream>
#include <string>

using namespace std;

TipoBonus::TipoBonus(void) : tieneError(false), utilizado(false)
{
	this->populateValidAttributes();
}

TipoBonus::TipoBonus(std::string& n, std::string& t) : tieneError(false), utilizado(false), nombre(n), nombreTextura(t)
{
	this->populateValidAttributes();
}

TipoBonus::TipoBonus(XmlElement& e) : tieneError(false), utilizado(false)
{
	this->populateValidAttributes();
	this->tieneError = !this->validateAttributes(e);
	
	if(e.hasAttribute("nombre"))
	{
		this->nombre = e.getValue("nombre");
	}

	if(e.hasAttribute("textura"))
	{
		this->nombreTextura = e.getValue("textura");
	}
}

std::string TipoBonus::getNombre(void)
{
	return nombre;
}

std::string TipoBonus::getNombreTextura(void)
{
	return nombreTextura;
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

void TipoBonus::setTextura(Textura & t)
{
	this->textura = t;
}