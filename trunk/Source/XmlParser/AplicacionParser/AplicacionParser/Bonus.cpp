#include "StdAfx.h"
#include "Bonus.h"

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

Bonus::Bonus(void)
{
}

std::string Bonus::getTipo()
{
	return tipo;
}

Bonus::~Bonus(void)
{
}
