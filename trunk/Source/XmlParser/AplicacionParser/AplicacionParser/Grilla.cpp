#include "StdAfx.h"
#include "Grilla.h"
#include "Camino.h"
#include "Obstaculo.h"
#include <exception>

Grilla::Grilla(int an, int al, std::string& topd)
{
	if (an < 0 || al < 0)
	{
		Logger::getInstance()->logWarning("En Grilla, ancho o alto menores que cero; se setean valores por defecto. \0");
		// Se setean valores por defecto
		ancho	= defGridAncho;
		alto	= defGridAlto;
		throw std::exception();
	}
	else
	{
		ancho = an;
		alto = al;
	}
	
	tipoObstaculoPorDefecto = topd;
}

Grilla::Grilla(XmlElement& e, List<TipoObstaculo>& lo, List<TipoBonus>& lb)
{
	tiposObstaculos = lo;
	tiposBonus = lb;

	if (e.hasAttribute("ancho")) 
	{
		std::string anchoString = e.getValue("ancho");
		int an = atoi(anchoString.c_str());
		
		if (an < 0)
		{
			// Se loguea el warning y se setea ancho por defecto
			Logger::getInstance()->logWarning("En Grilla, ancho menor a cero; se setea valor por defecto. \0");
			ancho = defGridAncho;
		}
		else
		{
			ancho = an;
		}

		
	}

	if(e.hasAttribute("alto"))
	{
		std::string altoString = e.getValue("alto");
		int al = atoi(altoString.c_str());
		
		if (al < 0)
		{
			// Se loguea el warning y se setea alto por defecto
			Logger::getInstance()->logWarning("En Grilla, alto menor a cero; se setea valor por defecto. \0");
			alto = defGridAlto;
		}
		else
		{
			alto = al;
		}
	}

	if (e.hasAttribute("tipoObstaculoPorDefecto"))
	{
		tipoObstaculoPorDefecto = e.getValue("tipoObstaculoPorDefecto");
	}

	else
	{
		// Logger, el tipo obstaculo por defecto es necesario.
		Logger::getInstance()->logWarning("En Grilla, el tipo obstaculo no fue definido; se toma tipo obstáculo por defecto. \0");
	}

	if (e.hasChildren())
	{
		generarMatriz(e.getChildren());
	}
}

Grilla::Grilla(void)
{
}

int Grilla::getAlto()
{
	return alto;
}

int Grilla::getAncho()
{
	return ancho;
}

List<List<Celda>> Grilla::getMatriz()
{
	return matriz;
}

std::string Grilla::getTipoObstaculoPorDefecto()
{
	return tipoObstaculoPorDefecto;
}

Grilla::~Grilla(void)
{
}

// métodos privados
void Grilla::generarMatriz(List<XmlElement>& listaElementos)
{
	for (size_t i = 0; i < this->alto; i++)
	{
		//agrego fila
		this->matriz.add(List<Celda>());
		for (size_t j = 0; j < this->ancho; j++)
		{
			//lleno fila
			this->matriz.at(i).add(Celda());
		}	
	}
	
	for (size_t i = 0; i < listaElementos.length(); i++)
	{
		if (listaElementos.at(i).getName() == "camino")
		{
			Camino cam(listaElementos.at(i));
			
			if(cam.hasBonus())
			{
				std::string tipoBonus = cam.getBonus().getTipo();

				bool bonusValido = verificarTipoBonusExistente(tipoBonus);

				if(!bonusValido)
				{
					//Logger bonus inexistente
					Logger::getInstance()->logError("En Grilla, bonus inexistente; se ignora el camino. \0");
					continue;
				}
			}
			bool result = colocarCeldaEnMatriz(cam);

			if(!result)
			{
				//Logger no se pudo meter elemento porque ya esta ocupada la posicion
				Logger::getInstance()->logError("En Grilla, no se pudo colocar el camino; posicion ya ocupada. \0");
			}
		}

		else if (listaElementos.at(i).getName() == "obstaculo")
		{
			Obstaculo obs(listaElementos.at(i));

			if(obs.getTipo() != "")
			{
				std::string tipoObstaculo = obs.getTipo();

				bool obstaculoValido = verificarTipoObstaculoExistente(tipoObstaculo);

				if(!obstaculoValido)
				{
					//Logger obstaculo inexistente
					Logger::getInstance()->logError("En Grilla, obstaculo inexistente; se ignora el obstaculo. \0");
					continue;
				}
			}

			else
			{
				obs.setTipo(tipoObstaculoPorDefecto);
			}

			bool result = colocarCeldaEnMatriz(obs);

			if(!result)
			{
				//Logger no se pudo meter elemento porque ya está ocupada la posicion
				Logger::getInstance()->logError("En Grilla, no se pudo colocar el obstaculo; posicion ya ocupada.");
			}
		}

		else
		{
			//Logger (tag con nombre incorrecto) y sigue
			Logger::getInstance()->logError("En Grilla, se ignora tag desconocido '"+listaElementos.at(i).getName()+"'.");
		}
	}
}

bool Grilla::colocarCeldaEnMatriz(Celda& c)
{
	int fila = c.getFila();
	int columna = c.getColumna();

	if (fila > alto)
	{
		//Logger y valor por defecto
		Logger::getInstance()->logWarning("En Grilla, celda con fila mayor al alto de la grilla; se asigna valor por defecto.");
	}

	if (columna > ancho)
	{
		//Logger y valor por defecto
		Logger::getInstance()->logWarning("En Grilla, celda con  columna mayor al ancho de la grilla; se asigna columna por defecto.");
	}

	if (c.esOcupada())
	{
		return false;
	}

	matriz.at(fila).at(columna) = c;

	matriz.at(fila).at(columna).Ocupar();


	return true;
}

bool Grilla::verificarTipoBonusExistente(std::string tb)
{
	for (size_t i = 0; i < tiposBonus.length(); i++)
	{
		if (tb == tiposBonus.at(i).getNombre())
		{
			return true;
		}
	}

	return false;
}

bool Grilla::verificarTipoObstaculoExistente(std::string to)
{
	for(size_t i = 0; i < tiposObstaculos.length(); i++)
	{
		if (to == tiposObstaculos.at(i).getNombre())
		{
			return true;
		}
	}

	return false;
}