#include "StdAfx.h"
#include "Obstaculo.h"
#include "Logger.h"
#include <sstream>

using namespace std;

Obstaculo::Obstaculo(std::string& t, int f, int c) : Celda(f, c), tipo(t), tieneError(false)
{
	this->populateValidAttributes();
}

Obstaculo::Obstaculo(XmlElement& e) : tieneError(false)
{
	if (e.hasChildren())
	{
		stringstream msg;
		msg << "Elemento Obstaculo tiene hijos, lo cual no es posible. Linea: " << e.getStartLine();
		Logger::getInstance()->logWarning(msg.str());
	}
	
	this->populateValidAttributes();
	this->tieneError = !this->validateAttributes(e);
	if (e.hasAttribute("tipo"))
	{
		tipo = e.getValue("tipo");
	}

	else
	{
		tipo = "";
	}

	if (e.hasAttribute("fila"))
	{
		std::string filaString = e.getValue("fila");
		int f = atoi(filaString.c_str());

		if(f < 0)
		{
			// Loggeo como Error que la fila sea menor a cero
			std::stringstream nroLinea;	nroLinea << e.getStartLine();
			Logger::getInstance()->logError("Línea " + nroLinea.str() + " -> En Obstaculo, fila menor a cero.");
		}

		fila = f;
	}

	if(e.hasAttribute("columna"))
	{
		std::string columnaString = e.getValue("columna");
		int c = atoi(columnaString.c_str());

		if (c < 0)
		{
			// Loggeo como Error que la fila sea menor a cero
			std::stringstream nroLinea;	nroLinea << e.getStartLine();
			Logger::getInstance()->logError("Línea " + nroLinea.str() + " -> En Obstaculo, columna menor a cero.");
		}

		columna = c;
	}
}

std::string Obstaculo::getTipo()
{
	return tipo;
}

void Obstaculo::setTipo(std::string t)
{
	tipo = t;
}

void Obstaculo::setTipoObstaculo(TipoObstaculo to)
{
	tipoObstaculo = to;
}

TipoObstaculo Obstaculo::getTipoObstaculo()
{
	return tipoObstaculo;
}

Obstaculo::~Obstaculo(void)
{
}

std::string Obstaculo::obtenerRepresentacion(Celda* celSup, Celda* celInf, Celda* celDer, Celda* celIzq)
{
	return this->getTipoObstaculo().getTextura().getPath();
}

Celda* Obstaculo::copiar(void)
{
	Obstaculo* obstaculo = new Obstaculo(this->tipo, this->fila, this->columna);
	obstaculo->ocupada = this->ocupada;
	obstaculo->tipoObstaculo = this->tipoObstaculo;
	obstaculo->tieneError = this->tieneError;
	return obstaculo;
}

bool Obstaculo::validateAttributes(XmlElement& e)
{
	List<XmlAttribute> attributes = e.getAttributes();
	size_t len = attributes.length();

	for (size_t i = 0; i < len; i++)
	{
		XmlAttribute att = attributes[i];
		if (!this->validAttributes.contains(att.getKey()))
		{
			stringstream msg;
			msg << "Clave de atributo: " << att.getKey() << " no es válida para el Obstaculo. Linea: " << e.getStartLine();
			Logger::getInstance()->logError(msg.str());
			return false;
		}
	}

	return true;
}

void Obstaculo::populateValidAttributes(void)
{
	this->validAttributes.add("fila");
	this->validAttributes.add("columna");
	this->validAttributes.add("tipo");
}

bool Obstaculo::hasError(void)
{
	return this->tieneError || this->tipoObstaculo.hasError();
}

void Obstaculo::setError(void)
{
	this->tieneError = true;
}