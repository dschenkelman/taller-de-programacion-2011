#include "StdAfx.h"
#include "Textura.h"
#include <string>
#include "Logger.h"
#include <sstream>
#include <limits>

using namespace std;

Textura::Textura(void)
{
}

Textura::Textura(XmlElement &element) : path(""), nombre(""), tieneError(false),
left(0), top(0), right(numeric_limits<int>::max()), bottom(numeric_limits<int>::max())
{
	this->populateValidAttributes();
	this->tieneError = !this->validateAttributes(element);

	this->getNameFromElement(element);
	this->getPathFromElement(element);
	this->getBoundsFromElement(element);
}

string Textura::getPath()
{
	return this->path;
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
	this->validAttributes.add("path");
	this->validAttributes.add("bottom");
	this->validAttributes.add("right");
	this->validAttributes.add("left");
	this->validAttributes.add("top");
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

int Textura::getLeft()
{
	return this->left;
}

int Textura::getTop()
{
	return this->top;
}

int Textura::getRight()
{
	return this->right;
}

int Textura::getBottom()
{
	return this->bottom;
}

//private methods
void Textura::getNameFromElement(XmlElement &element)
{
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
}


void Textura::getPathFromElement(XmlElement& element)
{
	if (element.hasAttribute("path"))
	{
		this->path = element.getValue("path");
	}
	else
	{
		stringstream msg;
		msg << "La textura no tiene el atributo 'path'. Linea: " << element.getStartLine();
		Logger::getInstance()->logError(msg.str());
		this->tieneError = true;
	}
}

void Textura::getBoundsFromElement(XmlElement& element)
{
	if (element.hasAttribute("left"))
	{
		int temp = atoi(element.getValue("left").c_str());
		this->left = temp > 0 ? temp : this->left;
	}

	if (element.hasAttribute("top"))
	{
		int temp = atoi(element.getValue("top").c_str());
		this->top = temp > 0 ? temp : this->top;
	}

	if (element.hasAttribute("right"))
	{
		int temp = atoi(element.getValue("right").c_str());
		if (temp > 0)
		{
			if (temp > this->left)
			{
				this->right = temp;
			}
		}
	}
	
	if (element.hasAttribute("bottom"))
	{
		int temp = atoi(element.getValue("bottom").c_str());
		if (temp > 0)
		{
			if (temp > this->top)
			{
				this->bottom = temp;
			}
		}
	}
}