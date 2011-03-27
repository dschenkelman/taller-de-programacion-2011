#include "StdAfx.h"
#include "Obstaculo.h"

Obstaculo::Obstaculo(std::string t, size_t f, size_t c)
{
	tipo = t;
	fila = f;
	columna = c;
}

Obstaculo::Obstaculo(XmlElement e)
{
	if (e.hasAttribute("fila") && e.hasAttribute("columna") && e.hasAttribute("tipo"))
	{
		tipo = e.getValue("tipo");
		//fila = e.getValue("fila");
		//columna = e.getValue("columna");
	}
}

std::string Obstaculo::getTipo()
{
	return tipo;
}

Obstaculo::~Obstaculo(void)
{
}
