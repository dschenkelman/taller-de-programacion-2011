#include "StdAfx.h"
#include "Bonus.h"

Bonus::Bonus(void)
{
}

Bonus::Bonus(XmlElement e)
{
	if (e.hasAttribute("tipo"))
	{
		tipo = e.getValue("tipo");
	}	
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

Bonus::~Bonus(void)
{
}