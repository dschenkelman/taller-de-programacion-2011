#include "StdAfx.h"
#include "Grilla.h"
#include <exception>

Grilla::Grilla(size_t an, size_t al, std::string topd)
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
	if (e.hasAttribute("ancho") && e.hasAttribute("alto") && e.hasAttribute("tipoObstaculoPorDefecto"))
	{
		//ancho = e.getValue("ancho");
		//alto = e.getValue("alto");
		tipoObstaculoPorDefecto = e.getValue("tipoObstaculoPorDefecto");
	}

	//generarMatriz(e.getChildren());
}

size_t Grilla::getAlto()
{
	return alto;
}

size_t Grilla::getAncho()
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
