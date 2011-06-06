#include "StdAfx.h"
#include "TipoBonus.h"
#include "Logger.h"
#include <sstream>
#include <string>

using namespace std;

TipoBonus::TipoBonus(void) : tieneError(false), utilizado(false),nombre(""), nombreTextura(""),
unidad("pasos"), duracion(100), probabilidad(1), apariciones(1) 
{
	this->populateValidAttributes();
}

TipoBonus::TipoBonus(std::string& n, std::string& t) : tieneError(false), utilizado(false), nombre(n), nombreTextura(t),
unidad("pasos"), duracion(100), probabilidad(1), apariciones(1)
{
	this->populateValidAttributes();
}

TipoBonus::TipoBonus(XmlElement& e) : tieneError(false), utilizado(false), nombre(""), nombreTextura(""),
unidad("pasos"), duracion(100), probabilidad(1), apariciones(1)
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

	if(e.hasAttribute("unidad"))
	{
		// default pasos
		string u = e.getValue("unidad");
		if (u == "tiempo")
		{
			this->unidad = u;
		} 
	}

	if (e.hasAttribute("duracion"))
	{
		string d = e.getValue("duracion");
		int dur = atoi(d.c_str());
		if (dur > 0)
		{
			this->duracion = dur;
		}
	}

	if (e.hasAttribute("probabilidad"))
	{
		string p = e.getValue("probabilidad");
		int prob = atoi(p.c_str());
		if (prob > 0)
		{
			this->probabilidad = prob;
		}
	}

	if (e.hasAttribute("apariciones"))
	{
		string a = e.getValue("apariciones");
		int ap = atoi(a.c_str());
		if (ap > 0)
		{
			this->apariciones = ap;
		}
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
	this->validAttributes.add("duracion");
	this->validAttributes.add("unidad");
	this->validAttributes.add("probabilidad");
	this->validAttributes.add("apariciones");
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

Textura& TipoBonus::getTextura(void)
{
	return this->textura;
}

int TipoBonus::getProbabilidad()
{
	return this->probabilidad;
}

int TipoBonus::getApariciones()
{
	return this->apariciones;
}

void TipoBonus::decreaseApariciones()
{
	this->apariciones--;
}
int TipoBonus::getDuracion(void){
	return this->duracion;
}
