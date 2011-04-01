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

Grilla::Grilla(XmlElement& e)
{
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

	//generarMatriz(e.getChildren());
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

// método privado
void Grilla::generarMatriz(List<XmlElement>& listaElementos)
{
	for (size_t i = 0; i < listaElementos.length(); i++)
	{
		if (listaElementos.at(i).getName() == "camino")
		{
			Camino cam(listaElementos.at(i));
			bool result = colocarCeldaEnMatriz(cam);

			if(!result)
			{
				//Logger no se pudo meter elemento porque ya esta ocupada la posicion
			}
		}

		if (listaElementos.at(i).getName() == "obstaculo")
		{
			Obstaculo obs(listaElementos.at(i));
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

	//verificar si está ocupada

	matriz.at(fila).at(columna) = c;

	return true;
}