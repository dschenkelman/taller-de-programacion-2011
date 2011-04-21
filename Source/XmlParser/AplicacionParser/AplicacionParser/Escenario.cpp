#include "StdAfx.h"
#include "Escenario.h"
#include <sstream>
using namespace std;

Escenario::Escenario(void): tieneError(false)
{
}

Escenario::Escenario(XmlElement& e) : tieneError(false)
{
	if (e.getName() != "escenario")
	{
		stringstream msg;
		msg << "El nombre del elemento raiz no es escenario. Al ser fundamental se lo considera como tal. Linea: " << e.getStartLine();
		Logger::getInstance()->logWarning(msg.str());		
	}

	this->populateValidAttributes();
	this->tieneError = !this->validateAttributes(e);
	Grilla miGrilla;

	if (e.hasChildren())
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
	else{
		this->grilla = miGrilla;
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
	List<string> listaTexturas;
	bool found = false;

	for(size_t i = 0; i < listaElementos.length(); i++)
	{
		if(listaElementos.at(i).getName() == "tiposbonus")
		{
			found = true;
			if (listaElementos.at(i).hasChildren())
			{
				List<XmlElement> listaBonusXml = listaElementos.at(i).getChildren();
			
				for(size_t j = 0; j < listaBonusXml.length(); j++)
				{
					if(listaBonusXml.at(j).hasAttribute("nombre") && listaBonusXml.at(j).hasAttribute("textura"))
					{
						TipoBonus tb(listaBonusXml.at(j));
						tb.setLinea(listaBonusXml.at(j).getStartLine());
						listaBonus.add(tb);

						bool texturaExistente = listaTexturas.contains(tb.getTextura());
						if(texturaExistente)
						{
							stringstream msg;
							msg << "La textura asignada para el tipo bonus " <<
								tb.getNombre() + " está repetida. Linea: " << listaBonusXml.at(j).getStartLine();
							Logger::getInstance()->logWarning(msg.str());
						}
						else
						{
							listaTexturas.add(tb.getTextura());
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
				stringstream msg;
				msg << "La lista de tipos bonus esta vacia. Linea: " << listaElementos.at(i).getStartLine();
				Logger::getInstance()->logWarning(msg.str());
			}
		}
	}

	if (!found)
	{
		//Logger, no hay lista de tipos bonus
		Logger::getInstance()->logWarning("No existe lista de tipo bonus \0");
	}

	return listaBonus;
}

List<TipoObstaculo> Escenario::obtenerTiposObstaculos(List<XmlElement>& listaElementos)
{
	List<TipoObstaculo> listaObstaculos;
	List<string> listaTexturas;
	bool found = false;

	for(size_t i = 0; i < listaElementos.length(); i++)
	{
		if(listaElementos.at(i).getName() == "tiposobstaculos")
		{
			found = true;
			if (listaElementos.at(i).hasChildren())
			{			
				List<XmlElement> listaObstaculosXml = listaElementos.at(i).getChildren();
				
				for(size_t j = 0; j < listaObstaculosXml.length(); j++)
				{
					if(listaObstaculosXml.at(j).hasAttribute("nombre") && listaObstaculosXml.at(j).hasAttribute("textura"))
					{
						TipoObstaculo to(listaObstaculosXml.at(j));
						to.setLinea(listaObstaculosXml.at(j).getStartLine());
						listaObstaculos.add(to);

						bool texturaExistente = listaTexturas.contains(to.getTextura());
						if(texturaExistente)
						{
							stringstream msg;
							msg << "La textura asignada para el tipo obstaculo " + 
								to.getNombre() + " está repetida. Linea: " << listaObstaculosXml.at(j).getStartLine();
							Logger::getInstance()->logWarning(msg.str());
						}
						else
						{
							listaTexturas.add(to.getTextura());
						}
					}

					else
					{
						//Logger, tipo obstaculo invalido, le falta un atributo.
						stringstream msg;
						msg << "El tipo obstaculo en la linea " << listaObstaculosXml.at(j).getStartLine() <<
							" es inválido. No tiene asignado correctamente los atributos. Linea: " << listaObstaculosXml.at(j).getStartLine();
						Logger::getInstance()->logWarning(msg.str());
					}
				}
			}
			else
			{
				stringstream msg;
				msg << "La lista de tipos obstaculos esta vacia. Linea: " << listaElementos.at(i).getStartLine();
				Logger::getInstance()->logWarning(msg.str());
			}
		}
	}

	if (!found)
	{
		//Logger, no hay lista de tipo obstaculo
		Logger::getInstance()->logWarning("No existe lista de tipos obstaculos \0");
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

bool Escenario::hasError(void)
{
	return tieneError || this->grilla.hasError();
}

void Escenario::populateValidAttributes(void)
{
	this->validAttributes.add("nombre");
}

bool Escenario::validateAttributes(XmlElement& e)
{
	List<XmlAttribute> attributes = e.getAttributes();

	for(size_t i = 0; i < attributes.length(); i++)
	{
		XmlAttribute att = attributes.at(i);

		if (!validAttributes.contains(att.getKey()))
		{
			stringstream msg;
			msg << "Clave de atributo: " << att.getKey() << " no es válida para el Escenario. Linea: " << e.getStartLine();
			Logger::getInstance()->logError(msg.str());
			return false;
		}
	}

	return true;
}