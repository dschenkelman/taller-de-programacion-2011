#include "StdAfx.h"
#include "Escenario.h"
#include <sstream>	

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
}

//metodos privados

List<TipoBonus> Escenario::obtenerTiposBonus(List<XmlElement>& listaElementos)
{
	List<TipoBonus> listaBonus;
	List<char> listaTexturas;

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

					bool texturaExistente = verificarTexturaEnLista(listaTexturas, tb.getTextura());
					if(texturaExistente)
					{
						Logger::getInstance()->logWarning("La textura asignada para el tipo bonus " + 
							tb.getNombre() + " está repetida \0");
					}

				}

				else
				{
					//Logger, tipo bonus invalido.
					std::stringstream nroLinea;	nroLinea << listaBonusXml.at(j).getStartLine();
					Logger::getInstance()->logWarning("El tipo bonus en la linea " + nroLinea.str() + 
						" es inválido, no tiene asignados correctamente los atributos \0");
				}
			}
		}

		else
		{
			//Logger, no hay lista de tipos bonus
			Logger::getInstance()->logWarning("No existe lista de tipo bonus \0");
		}
	}

	return listaBonus;
}

List<TipoObstaculo> Escenario::obtenerTiposObstaculos(List<XmlElement>& listaElementos)
{
	List<TipoObstaculo> listaObstaculos;
	List<char> listaTexturas;

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

					bool texturaExistente = verificarTexturaEnLista(listaTexturas, to.getTextura());
					if(texturaExistente)
					{
						Logger::getInstance()->logWarning("La textura asignada para el tipo obstaculo " + 
							to.getNombre() + " está repetida \0");
					}
				}

				else
				{
					//Logger, tipo obstaculo invalido, le falta un atributo.
					std::stringstream nroLinea; nroLinea << listaObstaculosXml.at(j).getStartLine();
					Logger::getInstance()->logWarning("El tipo obstaculo en la linea " + nroLinea.str() +
						" es inválido. No tiene asignado correctamente los atributos \0");
				}
			}
		}

		else
		{
			//Logger, no hay lista de tipo obstaculo
			Logger::getInstance()->logWarning("No existe lista de tipos obstaculos \0");
		}
	}

	return listaObstaculos;
}

bool Escenario::verificarTexturaEnLista(List<char>& listaCaracteres, char t)
{
	for (size_t i = 0; i < listaCaracteres.length(); i++)
	{
		if (listaCaracteres.at(i) == t)
		{
			return true;
		}
	}

	return false;
}