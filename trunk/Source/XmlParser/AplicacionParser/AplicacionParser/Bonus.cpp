#include "StdAfx.h"
#include "Bonus.h"
#include "Logger.h"
#include <sstream>
#include "Image.h"
#include "Textura.h"

using namespace std;

Bonus::Bonus(void) : tieneError(false)
{
	this->populateValidAttributes();
}

Bonus::Bonus(XmlElement& e) : tieneError(false)
{
	if (e.hasChildren())
	{
		stringstream msg;
		msg << "Elemento Bonus tiene hijos, lo cual no es posible. Linea: " << e.getStartLine();
		Logger::getInstance()->logWarning(msg.str());
	}
	
	this->populateValidAttributes();
	this->tieneError = !this->validateAttributes(e);
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
	return this->tieneError || this->tipoBonus.hasError();
}

Image Bonus::obtenerRepresentacion(void)
{
	Textura textura = this->getTipoBonus().getTextura();
	Image imagen(textura.getPath());
	if (!imagen.hasError())
	{
		imagen.crop(textura.getTop(), textura.getLeft(), textura.getRight(), textura.getBottom());
		Uint32 alphaPixel = textura.getRed() | textura.getGreen() << 8 | textura.getBlue() << 16;
		imagen.rotate(textura.getRotation(), alphaPixel);
	}
	return imagen;	
}

Bonus::~Bonus(void)
{
}