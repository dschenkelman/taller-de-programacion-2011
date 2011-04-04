#include "StdAfx.h"
#include "Escenario.h"

Escenario::Escenario(void)
{
}

Escenario::Escenario(XmlElement& e)
{
	tiposBonus = obtenerTiposBonus(e.getChildren());
	tiposObstaculos = obtenerTiposObstaculos(e.getChildren());
	
	for(size_t i = 0; i < e.getChildren().length(); i++)
	{
		if (e.getChildren().at(i).getName() == "grilla")
		{
			this->grilla = Grilla(e.getChildren().at(i), tiposObstaculos, tiposBonus);
		}
	}
}

Grilla& Escenario::getGrilla()
{
	return grilla;
}

std::string Escenario::getNombre()
{
	return nombre;
}

List<TipoBonus> Escenario::getTiposBonus()
{
	return tiposBonus;
}

List<TipoObstaculo> Escenario::getTiposObstaculos()
{
	return tiposObstaculos;
}

Escenario::~Escenario(void)
{
	this->grilla.destruir();
}

//metodos privados

List<TipoBonus> Escenario::obtenerTiposBonus(List<XmlElement>& listaElementos)
{
	List<TipoBonus> listaBonus;

	for(size_t i = 0; i < listaElementos.length(); i++)
	{
		if(listaElementos.at(i).getName() == "tiposBonus")
		{
			List<XmlElement> listaBonusXml = listaElementos.at(i).getChildren();
			
			for(size_t j = 0; j < listaBonusXml.length(); j++)
			{
				if(listaBonusXml.at(j).hasAttribute("nombre") && listaBonusXml.at(j).hasAttribute("textura"))
				{
					TipoBonus tb(listaBonusXml.at(j));
					listaBonus.add(tb);
				}

				else
				{
					//Logger, tipo bonus invalido.
				}
			}
		}

		else
		{
			//Logger, no hay lista de tipos bonus
		}
	}

	return listaBonus;
}

List<TipoObstaculo> Escenario::obtenerTiposObstaculos(List<XmlElement>& listaElementos)
{
	List<TipoObstaculo> listaObstaculos;

	for(size_t i = 0; i < listaElementos.length(); i++)
	{
		if(listaElementos.at(i).getName() == "tiposObstaculos")
		{
			List<XmlElement> listaObstaculosXml = listaElementos.at(i).getChildren();
			
			for(size_t j = 0; j < listaObstaculosXml.length(); j++)
			{
				if(listaObstaculosXml.at(j).hasAttribute("nombre") && listaObstaculosXml.at(j).hasAttribute("textura"))
				{
					TipoObstaculo to(listaObstaculosXml.at(j));
					listaObstaculos.add(to);
				}

				else
				{
					//Logger, tipo obstaculo invalido, le falta un atributo.
				}
			}
		}

		else
		{
			//Logger, no hay lista de tipo obstaculo
		}
	}

	return listaObstaculos;
}