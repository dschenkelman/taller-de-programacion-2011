#include "StdAfx.h"
#include "Textura.h"
#include <string>
#include "Logger.h"
#include <sstream>

using namespace std;

Textura::Textura(void)
{
}

Textura::Textura(XmlElement &element) : archivo(""), nombre("")
{
	this->populateValidAttributes();
	this->tieneError = !this->validateAttributes(element);
	this->nombre = element.getValue("nombre");
	this->archivo = element.getValue("archivo");
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