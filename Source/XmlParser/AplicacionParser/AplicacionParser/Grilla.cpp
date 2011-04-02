#include "StdAfx.h"
#include "Grilla.h"
#include "Camino.h"
#include "Obstaculo.h"
#include <exception>

Grilla::Grilla(int an, int al, std::string& topd)
{
	if (an < 0 || al < 0)
	{
		throw std::exception();
	}

	ancho = an;
	alto = al;
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
			throw std::exception();
		}

		ancho = an;
	}

	if(e.hasAttribute("alto"))
	{
		std::string altoString = e.getValue("alto");
		int al = atoi(altoString.c_str());
		
		if (al < 0)
		{
			throw std::exception();
		}

		alto = al;
	}

	if (e.hasAttribute("tipoObstaculoPorDefecto"))
	{
		tipoObstaculoPorDefecto = e.getValue("tipoObstaculoPorDefecto");
	}

	else
	{
		// Logger, el tipo obstaculo por defecto es necesario.
	}

	if (e.hasChildren())
	{
		generarMatriz(e.getChildren());
	}
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
					continue;
				}
			}
			bool result = colocarCeldaEnMatriz(cam);

			if(!result)
			{
				//Logger no se pudo meter elemento porque ya esta ocupada la posicion
			}
		}

		if (listaElementos.at(i).getName() == "obstaculo")
		{
			Obstaculo obs(listaElementos.at(i));

			if(obs.getTipo() != "")
			{
				std::string tipoObstaculo = obs.getTipo();

				bool obstaculoValido = verificarTipoObstaculoExistente(tipoObstaculo);

				if(!obstaculoValido)
				{
					//Logger obstaculo inexistente
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
			}
		}

		else
		{
			//Logger (tag con nombre incorrecto) y sigue
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
	}

	if (columna > ancho)
	{
		//Logger y valor por defecto
	}

	if (c.esOcupada())
	{
		return false;
	}

	matriz.at(fila).at(columna) = c;

	c.Ocupar();

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