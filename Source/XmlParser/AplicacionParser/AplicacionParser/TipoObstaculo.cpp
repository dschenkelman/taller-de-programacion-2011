#include "StdAfx.h"
#include "TipoObstaculo.h"
#include "Logger.h"
#include <sstream>

using namespace std;

TipoObstaculo::TipoObstaculo(XmlElement& e) : tieneError(false), utilizado(false), numeroLinea(e.getStartLine())
{
	this->populateValidAttributes();
	this->tieneError = !this->validateAttributes(e);

	if(e.hasAttribute("nombre"))
	{
		this->nombre = e.getValue("nombre");
	}

	if(e.hasAttribute("textura"))
	{
		this->textura = e.getValue("textura");
	}
}

TipoObstaculo::TipoObstaculo(void) : tieneError(false), utilizado(false)
{
}

TipoObstaculo::TipoObstaculo(std::string& n, std::string& t) : tieneError(false), utilizado(false), nombre(n), textura(t)
{
}

TipoObstaculo::~TipoObstaculo(void)
{
}

std::string TipoObstaculo::getNombre()
{
	return nombre;
}

std::string TipoObstaculo::getTextura()
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

bool TipoObstaculo::hasError(void)
{
	return this->tieneError;
}

bool TipoObstaculo::validateAttributes(XmlElement& e)
{
	List<XmlAttribute> attributes = e.getAttributes();
	size_t len = attributes.length();

	for (size_t i = 0; i < len; i++)
	{
		XmlAttribute att = attributes[i];
		if (!this->validAttributes.contains(att.getKey()))
		{
			stringstream msg;
			msg << "Clave de atributo: " << att.getKey() << " no es válida para el TipoObstaculo. Linea: " << e.getStartLine();
			Logger::getInstance()->logError(msg.str());
			return false;
		}
	}

	return true;
}

void TipoObstaculo::populateValidAttributes(void)
{
	this->validAttributes.add("nombre");
	this->validAttributes.add("textura");
}

void TipoObstaculo::setLinea(int l)
{
	this->numeroLinea = l;
}

int TipoObstaculo::getLinea(void)
{
	return this->numeroLinea;
}