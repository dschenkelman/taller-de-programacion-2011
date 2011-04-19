#include "StdAfx.h"
#include "Textura.h"
#include <string>
#include "Logger.h"
#include <sstream>

using namespace std;

Textura::Textura(void)
{
}

Textura::Textura(XmlElement &element) : archivo(""), nombre(""), tieneError(false)
{
	this->populateValidAttributes();
	this->tieneError = !this->validateAttributes(element);
	
	if (element.hasAttribute("nombre"))
	{
		this->nombre = element.getValue("nombre");
	}
	else
	{
		stringstream msg;
		msg << "La textura no tiene el atributo 'nombre'. Linea: " << element.getStartLine();
		Logger::getInstance()->logError(msg.str());
		this->tieneError = true;
	}

	if (element.hasAttribute("archivo"))
	{
		this->archivo = element.getValue("archivo");
	}
	else
	{
		stringstream msg;
		msg << "La textura no tiene el atributo 'archivo'. Linea: " << element.getStartLine();
		Logger::getInstance()->logError(msg.str());
		this->tieneError = true;
	}
}

string Textura::getArchivo()
{
	return this->archivo;
}

string Textura::getNombre()
{
	return this->nombre;
}

bool Textura::hasError()
{
	return this->tieneError;
}

Textura::~Textura(void)
{
}

void Textura::populateValidAttributes()
{
	this->validAttributes.add("nombre");
	this->validAttributes.add("archivo");
}

bool Textura::validateAttributes(XmlElement& element)
{
	List<XmlAttribute> attributes = element.getAttributes();
	size_t len = attributes.length();

	for (size_t i = 0; i < len; i++)
	{
		XmlAttribute att = attributes[i];
		if (!this->validAttributes.contains(att.getKey()))
		{
			stringstream msg;
			msg << "Clave de atributo: " << att.getKey() << " no es válida para la Textura. Linea: " << element.getStartLine();
			Logger::getInstance()->logError(msg.str());
			return false;
		}
	}

	return true;
}