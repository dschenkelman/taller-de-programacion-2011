#include "StdAfx.h"
#include "Escenario.h"
#include <sstream>
using namespace std;

Escenario::Escenario(void): tieneError(false)
{
}

Escenario::Escenario(XmlElement& e) : tieneError(false), texturaFondo("")
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

	this->getTexturaFondoFromElement(e);

	if (e.hasChildren())
	{
		this->texturas = obtenerTexturas(e.getChildren());
		this->tiposBonus = obtenerTiposBonus(e.getChildren());
		this->tiposObstaculos = obtenerTiposObstaculos(e.getChildren());

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

	this->validarTexturaFondoExiste(e.getStartLine());
}

Grilla& Escenario::getGrilla()
{
	return grilla;
}

std::string Escenario::getNombre()
{
	return nombre;
}

std::string Escenario::getTexturaFondo()
{
	return this->texturaFondo;
}

List<Textura> Escenario::getTexturas()
{
	return this->texturas;
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
						this->agregarTipoBonusSiExisteSuTextura(tb, listaBonus);

						bool texturaExistente = listaTexturas.contains(tb.getNombreTextura());
						if(texturaExistente)
						{
							stringstream msg;
							msg << "La textura asignada para el tipo bonus " <<
								tb.getNombre() + " está repetida. Linea: " << listaBonusXml.at(j).getStartLine();
							Logger::getInstance()->logWarning(msg.str());
						}
						else
						{
							listaTexturas.add(tb.getNombreTextura());
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
						this->agregarTipoObstaculoSiExisteSuTextura(to, listaObstaculos);

						bool texturaExistente = listaTexturas.contains(to.getNombreTextura());
						if(texturaExistente)
						{
							stringstream msg;
							msg << "La textura asignada para el tipo obstaculo " + 
								to.getNombre() + " está repetida. Linea: " << listaObstaculosXml.at(j).getStartLine();
							Logger::getInstance()->logWarning(msg.str());
						}
						else
						{
							listaTexturas.add(to.getNombreTextura());
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

List<Textura> Escenario::obtenerTexturas(List<XmlElement>& listaElementos)
{
	List<Textura> listaTexturas;
	bool found = false;

	for(size_t i = 0; i < listaElementos.length(); i++)
	{
		if(listaElementos.at(i).getName() == "texturas")
		{
			found = true;
			if (listaElementos.at(i).hasChildren())
			{			
				List<XmlElement> listaTexturasXml = listaElementos.at(i).getChildren();
				
				for(size_t j = 0; j < listaTexturasXml.length(); j++)
				{
					if(listaTexturasXml.at(j).hasAttribute("nombre") && listaTexturasXml.at(j).hasAttribute("path"))
					{
						Textura t(listaTexturasXml.at(j));
						t.setLine(listaTexturasXml.at(j).getStartLine());
						listaTexturas.add(t);
					}
					else
					{
						//Logger, tipo obstaculo invalido, le falta un atributo.
						stringstream msg;
						msg << "La textura en la linea " << listaTexturasXml.at(j).getStartLine() <<
							" es inválida. No tiene asignado correctamente los atributos. Linea: " << listaTexturasXml.at(j).getStartLine();
						Logger::getInstance()->logWarning(msg.str());
					}
				}
			}
			else
			{
				stringstream msg;
				msg << "La lista de texturas esta vacia. Linea: " << listaElementos.at(i).getStartLine();
				Logger::getInstance()->logWarning(msg.str());
			}
		}
	}

	if (!found)
	{
		//Logger, no hay lista de tipo obstaculo
		Logger::getInstance()->logWarning("No existe lista de texturas \0");
	}

	return listaTexturas;
}

bool Escenario::hasError(void)
{
	return tieneError || this->grilla.hasError();
}

void Escenario::populateValidAttributes(void)
{
	this->validAttributes.add("nombre");
	this->validAttributes.add("texturafondo");
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

void Escenario::getTexturaFondoFromElement(XmlElement & element)
{
	if (element.hasAttribute("texturafondo"))
	{
		this->texturaFondo = element.getValue("texturafondo");
	}
	else
	{
		stringstream msg;
		msg << "El escenario no tiene textura de fondo. Esto es un error y no se puede imprimir. Linea: " << element.getStartLine();
		Logger::getInstance()->logError(msg.str());
		this->tieneError = true;		
	}
}

void Escenario::agregarTipoBonusSiExisteSuTextura(TipoBonus& tb, List<TipoBonus>& listaBonus)
{
	bool found = false;
	
	for (size_t i = 0; i < this->texturas.length(); i++)
	{
		Textura t = this->texturas.at(i);
		if (t.getNombre() == tb.getNombreTextura())
		{
			found = true;
			tb.setTextura(t);
			listaBonus.add(tb);	
			break;
		}
	}

	if (!found)
	{
		stringstream msg;
		msg << "La textura asignada al tipo de bonus no existe. El tipo de bonus no será considerado. Linea: " << tb.getLinea();
		Logger::getInstance()->logWarning(msg.str());
		this->tieneError = true;		
	}
}

void Escenario::agregarTipoObstaculoSiExisteSuTextura(TipoObstaculo& to, List<TipoObstaculo>& listaObstaculos)
{
	bool found = false;
	
	for (size_t i = 0; i < this->texturas.length(); i++)
	{
		Textura t = this->texturas.at(i);
		if (t.getNombre() == to.getNombreTextura())
		{
			found = true;
			to.setTextura(t);
			listaObstaculos.add(to);	
			break;
		}
	}

	if (!found)
	{
		stringstream msg;
		msg << "La textura asignada al tipo de bonus no existe. El tipo de bonus no será considerado. Linea: " << to.getLinea();
		Logger::getInstance()->logWarning(msg.str());
		this->tieneError = true;		
	}
}

void Escenario::validarTexturaFondoExiste(int linea)
{
	bool found = false;

	for(size_t i = 0; i < this->texturas.length(); i++)
	{
		if (this->texturas.at(i).getNombre() == this->texturaFondo)
		{
			found = true;
			this->texturas.at(i).use();
		}
	}

	if (!found)
	{
		stringstream msg;
		msg << "La textura de fondo del escenario no existe. Esto es un error y no se puede imprimir. Linea: " << linea;
		Logger::getInstance()->logError(msg.str());
		this->tieneError = true;
	}
}