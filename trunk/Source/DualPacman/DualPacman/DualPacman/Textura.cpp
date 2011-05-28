#include "StdAfx.h"
#include "Textura.h"
#include <string>
#include "Logger.h"
#include <sstream>
#include <limits>

using namespace std;

Textura::Textura(void) : path(""), nombre(""), tieneError(false),
left(0), top(0), right(numeric_limits<int>::max()), bottom(numeric_limits<int>::max()),
red(255), green(0), blue(255), delta(0), rotation(0), line(0), usada(false)
{

}

Textura::Textura(string imagePath) : path(imagePath), nombre(""), tieneError(false),
left(0), top(0), right(numeric_limits<int>::max()), bottom(numeric_limits<int>::max()),
red(255), green(0), blue(255), delta(0), rotation(0), line(0), usada(false)
{
}

Textura::Textura(XmlElement &element) : path(""), nombre(""), tieneError(false),
left(0), top(0), right(numeric_limits<int>::max()), bottom(numeric_limits<int>::max()),
red(255), green(0), blue(255), delta(0), rotation(0), line(0), usada(false)
{
	this->populateValidAttributes();
	this->tieneError = !this->validateAttributes(element);

	this->getNameFromElement(element);
	this->getPathFromElement(element);
	this->getBoundsFromElement(element);
	this->getAlphaFromElement(element);
	this->getDeltaFromElement(element);
	this->getRotationFromElement(element);
}

void Textura::setLine(int l)
{
	this->line = l;
}

int Textura::getLine(void)
{
	return this->line;
}

string Textura::getPath()
{
	return this->path;
}

string Textura::getNombre()
{
	return this->nombre;
}

void Textura::setNombre(string n)
{
	this->nombre = n;
}

bool Textura::isUsed()
{
	return this->usada;
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
	this->validAttributes.add("alpha");
	this->validAttributes.add("delta");
	this->validAttributes.add("rot");
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

int Textura::getRed()
{
	return this->red;
}

int Textura::getGreen()
{
	return this->green;
}

int Textura::getBlue()
{
	return this->blue;
}


int Textura::getDelta(void)
{
	return this->delta;
}

int Textura::getRotation(void)
{
	return this->rotation;
}

void Textura::use(void)
{
	this->usada = true;
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

void Textura::getAlphaFromElement(XmlElement& element)
{
	if (element.hasAttribute("alpha"))
	{
		string hex = element.getValue("alpha");
		
		if (this->validateHex(hex))
		{
			string r = hex.substr(1,2);
			string g = hex.substr(3,2);
			string b = hex.substr(5,2);

			std::stringstream ssRed;
			ssRed << std::hex << r;
			ssRed >> this->red;

			std::stringstream ssGreen;
			ssGreen << std::hex << g;
			ssGreen >> this->green;

			std::stringstream ssBlue;
			ssBlue << std::hex << b;
			ssBlue >> this->blue;
		}
		else
		{
			stringstream msg;
			msg << "El formato del valor del atributo 'alpha' no es válido. Formato válido: #rrggbb." 
				<< " Se usa el valor por defecto #FF00FF. Linea: " << element.getStartLine();
			Logger::getInstance()->logError(msg.str());
		}
	}
}

void Textura::getBoundsFromElement(XmlElement& element)
{
	if (element.hasAttribute("left"))
	{
		int temp = atoi(element.getValue("left").c_str());
		if (temp > 0)
		{
			this->left = temp;
		}
		else
		{
			stringstream msg;
			msg << "El atributo left tiene un valor inválido. Por defecto se usará 0. Linea: " << element.getStartLine();
			Logger::getInstance()->logError(msg.str());
		}
	}

	if (element.hasAttribute("top"))
	{
		int temp = atoi(element.getValue("top").c_str());
		if (temp > 0)
		{
			this->top = temp;
		}
		else
		{
			stringstream msg;
			msg << "El atributo top tiene un valor inválido. Por defecto se usará 0. Linea: " << element.getStartLine();
			Logger::getInstance()->logError(msg.str());
		}
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
			else
			{
				stringstream msg;
				msg << "El atributo right es menor que left. Por defecto, se usará el ancho de la imágen. Linea: " << element.getStartLine();
				Logger::getInstance()->logError(msg.str());
			}
		}
		else
		{
			stringstream msg;
			msg << "El atributo right tiene un valor inválido. Por defecto, se usará el ancho de la imágen. Linea: " << element.getStartLine();
			Logger::getInstance()->logError(msg.str());
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
			else
			{
				stringstream msg;
				msg << "El atributo bottom es menor que top. Por defecto, se usará el alto de la imágen. Linea: " << element.getStartLine();
				Logger::getInstance()->logError(msg.str());
			}
		}
		else
		{
			stringstream msg;
			msg << "El atributo bottom es tiene un valor inválido. Por defecto, se usará el alto de la imágen. Linea: " << element.getStartLine();
			Logger::getInstance()->logError(msg.str());
		}
	}
}

bool Textura::validateHex(std::string &hex)
{
	if (hex.at(0) != '#' || hex.length() != 7)
	{
		return false;
	}

	// get color part
	string color = hex.substr(1);

	for (size_t i = 0; i < color.length(); i++)
	{
		char c = color.at(i);
		char lowerC = tolower(c);
		if (!isdigit(lowerC) &&
			!((lowerC >='a') && (lowerC <= 'f')))
		{
			return false;
		}
	}

	return true;
}

void Textura::getDeltaFromElement(XmlElement& element)
{
	if (element.hasAttribute("delta"))
	{
		int temp = atoi(element.getValue("delta").c_str());
		if (temp > 0)
		{
			this->delta = temp;
		}
		else
		{
			stringstream msg;
			msg << "El valor del atributo delta es inválido. Debe ser un entero positivo. Por defecto, se usará 0. Linea: " << element.getStartLine();
			Logger::getInstance()->logError(msg.str());
		}
	}
}

void Textura::getRotationFromElement(XmlElement& element)
{
	if (element.hasAttribute("rot"))
	{
		int temp = atoi(element.getValue("rot").c_str());
		if (temp > 0 && temp < 360)
		{
			this->rotation = temp;
		}
		else
		{
			stringstream msg;
			msg << "El valor del atributo rotación es inválido. Debe ser un entero entre 0 y 359. Por defecto, se usará 0. Linea: " << element.getStartLine();
			Logger::getInstance()->logError(msg.str());
		}
	}
}