#include "StdAfx.h"
#include "Grilla.h"
#include <exception>

Grilla::Grilla(int an, int al, std::string topd)
{
	if (an < 0 || al < 0)
	{
		throw std::exception();
	}

	ancho = an;
	alto = al;
	tipoObstaculoPorDefecto = topd;
}

Grilla::Grilla(XmlElement e)
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
bool Grilla::generarMatriz(List<XmlElement> listaElementos)
{
	return true;
}
