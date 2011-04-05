#include "StdAfx.h"
#include "Grilla.h"
#include "Camino.h"
#include "Obstaculo.h"
#include <exception>

Grilla::Grilla(int an, int al, std::string& topd) : matrizGenerada(false)
{
	if (an < 0 || al < 0)
	{
		Logger::getInstance()->logWarning("En Grilla, ancho o alto menores que cero; se setean valores por defecto. \0");
		// Se setean valores por defecto
		ancho = defGridAncho;
		alto = defGridAlto;
		throw std::exception();
	}
	else
	{
		ancho = an;
		alto = al;
	}
	
	tipoObstaculoPorDefecto = topd;
}

Grilla::Grilla(XmlElement& e, List<TipoObstaculo>& lo, List<TipoBonus>& lb) : matrizGenerada(false)
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

	verificarTiposUtilizados();
}

Grilla::Grilla(void) : matrizGenerada(false)
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

List<List<Celda*>>& Grilla::getMatriz()
{
	return this->matriz;
}

std::string Grilla::getTipoObstaculoPorDefecto()
{
	return tipoObstaculoPorDefecto;
}

Grilla::~Grilla(){}

void Grilla::destruir(void)
{
	if (this->matrizGenerada)
	{
		for (size_t i = 0; i < this->alto; i++)
		{
			for (size_t j = 0; j < this->ancho; j++)
			{
				//borro celda
				delete this->matriz.at(i).at(j);
			}	
		}
	}
}

// métodos privados
void Grilla::generarMatriz(List<XmlElement>& listaElementos)
{
	for (size_t i = 0; i < this->alto; i++)
	{
		//agrego fila
		this->matriz.add(List<Celda*>());
		for (size_t j = 0; j < this->ancho; j++)
		{
			//lleno fila
			this->matriz.at(i).add(new Celda(0,0));
		}	
	}

	this->matrizGenerada = true;
	
	for (size_t i = 0; i < listaElementos.length(); i++)
	{
		if (listaElementos.at(i).getName() == "camino")
		{
			Camino* cam = new Camino(listaElementos.at(i));
			
			if(cam->hasBonus())
			{
				std::string tipoBonus = cam->getBonus().getTipo();

				bool bonusValido = verificarTipoBonusExistente(tipoBonus);

				if(!bonusValido)
				{
					//Logger bonus inexistente
					Logger::getInstance()->logError("En Grilla, bonus inexistente; se ignora el camino. \0");
					delete cam;
					continue;
				}

				cam->getBonus().setTipoBonus(obtenerTipoBonus(tipoBonus));
			}
			bool result = colocarCeldaEnMatriz(cam);

			if(!result)
			{
				//Logger no se pudo meter elemento porque ya esta ocupada la posicion
				Logger::getInstance()->logWarning("En Grilla, no se pudo colocar el camino; posicion ya ocupada. \0");
			}
		}

		else if (listaElementos.at(i).getName() == "obstaculo")
		{
			Obstaculo* obs = new Obstaculo(listaElementos.at(i));

			if(obs->getTipo() == "")
			{
				obs->setTipo(tipoObstaculoPorDefecto);
			}
			
			std::string tipoObstaculo = obs->getTipo();

			bool obstaculoValido = verificarTipoObstaculoExistente(tipoObstaculo);

			if(!obstaculoValido)
			{
				//Logger obstaculo inexistente
				Logger::getInstance()->logError("En Grilla, obstaculo inexistente; se ignora el obstaculo. \0");
				delete obs;
				continue;
			}

			obs->setTipoObstaculo(obtenerTipoObstaculo(tipoObstaculo));

			bool result = colocarCeldaEnMatriz(obs);

			if(!result)
			{
				//Logger no se pudo meter elemento porque ya está ocupada la posicion
				Logger::getInstance()->logWarning("En Grilla, no se pudo colocar el obstaculo; posicion ya ocupada.");
			}
		}

		else
		{
			//Logger (tag con nombre incorrecto) y sigue
			Logger::getInstance()->logError("En Grilla, se ignora tag desconocido '"+listaElementos.at(i).getName()+"'.");
		}
	}
}

bool Grilla::colocarCeldaEnMatriz(Celda* c)
{
	int fila = c->getFila();
	int columna = c->getColumna();

	if (fila > alto)
	{
		//Logger y valor por defecto
		Logger::getInstance()->logWarning("En Grilla, celda con fila mayor al alto de la grilla; se asigna valor por defecto.");
		fila = defFila;
	}

	if (columna > ancho)
	{
		//Logger y valor por defecto
		Logger::getInstance()->logWarning("En Grilla, celda con columna mayor al ancho de la grilla; se asigna columna por defecto.");
		columna = defColumna;
	}

	if (matriz.at(fila).at(columna)->esOcupada())
	{
		return false;
	}

	delete matriz.at(fila).at(columna);
	matriz.at(fila).at(columna) = c;

	matriz.at(fila).at(columna)->Ocupar();

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

TipoBonus Grilla::obtenerTipoBonus(std::string tb)
{
	for(size_t i = 0; i < tiposBonus.length(); i++)
	{
		if (tb == tiposBonus.at(i).getNombre())
		{
			if (!tiposBonus.at(i).esUtilizado())
			{
				tiposBonus.at(i).utilizarTipo();
			}

			return tiposBonus.at(i);
		}
	}
}

TipoObstaculo Grilla::obtenerTipoObstaculo(std::string to)
{
	for(size_t i = 0; i < tiposObstaculos.length(); i++)
	{
		if (to == tiposObstaculos.at(i).getNombre())
		{
			if (!tiposObstaculos.at(i).esUtilizado())
			{
				tiposObstaculos.at(i).utilizarTipo();
			}

			return tiposObstaculos.at(i);
		}
	}
}

void Grilla::verificarTiposUtilizados()
{
	for (size_t i = 0; i < tiposBonus.length(); i++)
	{
		if(!tiposBonus.at(i).esUtilizado())
		{
			Logger::getInstance()->logWarning("El tipo bonus " + tiposBonus.at(i).getNombre() + " no está siendo utilizado");
		}
	}

	for (size_t i = 0; i < tiposObstaculos.length(); i++)
	{
		if(!tiposObstaculos.at(i).esUtilizado())
		{
			Logger::getInstance()->logWarning("El tipo obstaculo " + tiposObstaculos.at(i).getNombre() + " no está siendo utilizado");
		}
	}
}