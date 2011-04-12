#include "StdAfx.h"
#include "Grilla.h"
#include "Camino.h"
#include "Obstaculo.h"
#include <exception>
#include <sstream>
using namespace std;

Grilla::Grilla(int an, int al, std::string& topd) : matrizGenerada(false), tieneError(false)
{
	if (an < 0 || al < 0)
	{
		Logger::getInstance()->logWarning("En Grilla, ancho o alto menores que cero; se setean valores por defecto. \0");
		// Se setean valores por defecto
		ancho = defGridAncho;
		alto = defGridAlto;
		throw std::exception();
	}
	else
	{
		ancho = an;
		alto = al;
	}
	
	tipoObstaculoPorDefecto = topd;

	populateValidAttributes();
}

Grilla::Grilla(XmlElement& e, List<TipoObstaculo>& lo, List<TipoBonus>& lb) : matrizGenerada(false), tieneError(false), tipoObstaculoPorDefecto("")
{
	this->populateValidAttributes();
	this->tieneError = !this->validateAttributes(e);

	tiposObstaculos = lo;
	tiposBonus = lb;

	if (e.hasAttribute("ancho")) 
	{
		std::string anchoString = e.getValue("ancho");
		int an = atoi(anchoString.c_str());
		
		if (an < 0)
		{
			// Se loguea el warning y se setea ancho por defecto
			stringstream msg;
			msg << "En Grilla, ancho menor a cero; se setea valor por defecto. Linea: " << e.getStartLine();
			Logger::getInstance()->logWarning(msg.str());
			ancho = defGridAncho;
		}
		else
		{
			ancho = an;
		}

	}

	if(e.hasAttribute("alto"))
	{
		std::string altoString = e.getValue("alto");
		int al = atoi(altoString.c_str());
		
		if (al < 0)
		{
			// Se loguea el warning y se setea alto por defecto
			stringstream msg;
			msg << "En Grilla, alto menor a cero; se setea valor por defecto. Linea: " << e.getStartLine();
			Logger::getInstance()->logWarning(msg.str());
			alto = defGridAlto;
		}
		else
		{
			alto = al;
		}
	}

	if (e.hasAttribute("tipoobstaculopordefecto"))
	{
		this->tipoObstaculoPorDefecto = e.getValue("tipoobstaculopordefecto");
	}
	else
	{
		// Logger, el tipo obstaculo por defecto es necesario.
		stringstream msg;
		msg << "En Grilla, el tipo obstaculo por defecto no fue definido. No se puede graficar. Linea: " << e.getStartLine();
		Logger::getInstance()->logError(msg.str());
	}

	bool obstaculoValido = verificarTipoObstaculoExistente(this->tipoObstaculoPorDefecto);

	if (!obstaculoValido)
	{
		stringstream msg;
		msg << "En Grilla, el obstaculo por defecto definido no esta en la lista de obstaculos. Si es usado en algun casillero no se podra graficar. Linea: " << e.getStartLine();
		Logger::getInstance()->logWarning(msg.str());
	}

	if (e.hasChildren())
	{
		generarMatriz(e.getChildren());
	}

	verificarTiposUtilizados();
}

Grilla::Grilla(void) : matrizGenerada(false), tieneError(false)
{
}

int Grilla::getAlto()
{
	return alto;
}

int Grilla::getAncho()
{
	return ancho;
}

Celda* Grilla::getCelda(int fila, int columna)
{
	if (this->alto < fila || this->ancho < columna)
	{
		throw std::exception();
	}

	return this->matriz.at(fila).getValueAt(columna);
}

std::string Grilla::getTipoObstaculoPorDefecto()
{
	return tipoObstaculoPorDefecto;
}

Grilla::~Grilla()
{
	if (this->matrizGenerada)
	{
		for (size_t i = 0; i < this->alto; i++)
		{
			for (size_t j = 0; j < this->ancho; j++)
			{
				//borro celda
				delete this->matriz.at(i).at(j);
			}	
		}
	}
}

// métodos privados
void Grilla::generarMatriz(List<XmlElement>& listaElementos)
{
	for (size_t i = 0; i < this->alto; i++)
	{
		//agrego fila
		this->matriz.add(List<Celda*>());
		for (size_t j = 0; j < this->ancho; j++)
		{
			//lleno fila
			Obstaculo* o = new Obstaculo(this->tipoObstaculoPorDefecto, 0,0);
			bool obstaculoValido = verificarTipoObstaculoExistente(o->getTipo());
			if (obstaculoValido)
			{
				o->setTipoObstaculo(this->obtenerTipoObstaculo(o->getTipo()));
			}
			else
			{
				o->setError();
			}
			this->matriz.at(i).add(o);
		}	
	}

	this->matrizGenerada = true;
	
	for (size_t i = 0; i < listaElementos.length(); i++)
	{
		if (listaElementos.at(i).getName() == "camino")
		{
			Camino* cam = new Camino(listaElementos.at(i));
			
			if(cam->hasBonus())
			{
				std::string tipoBonus = cam->getBonus().getTipo();

				bool bonusValido = verificarTipoBonusExistente(tipoBonus);

				if(!bonusValido)
				{
					//Logger bonus inexistente
					stringstream msg;
					msg << "En Grilla, camino con bonus inexistente; no se puede imprimir. Linea: " << listaElementos.at(i).getStartLine();
					Logger::getInstance()->logError(msg.str());
					this->tieneError = true;
					delete cam;
					continue;
				}

				cam->getBonus().setTipoBonus(obtenerTipoBonus(tipoBonus));
			}
			bool result = colocarCeldaEnMatriz(cam, listaElementos.at(i).getStartLine());

			if (!result)
			{
				stringstream msg;
				msg << "En Grilla, no se pudo colocar el camino; posicion ya ocupada. Linea: " << listaElementos.at(i).getStartLine();
				Logger::getInstance()->logWarning(msg.str());
			}
		}

		else if (listaElementos.at(i).getName() == "obstaculo")
		{
			Obstaculo* obs = new Obstaculo(listaElementos.at(i));

			if(obs->getTipo() == "")
			{
				obs->setTipo(tipoObstaculoPorDefecto);
			}
			
			std::string tipoObstaculo = obs->getTipo();

			bool obstaculoValido = verificarTipoObstaculoExistente(tipoObstaculo);

			if(!obstaculoValido)
			{
				//Logger obstaculo inexistente
				stringstream msg;
				msg << "En Grilla, obstaculo inexistente; no se puede imprimir. Linea: " << listaElementos.at(i).getStartLine();
				Logger::getInstance()->logError(msg.str());
				this->tieneError = true;
				delete obs;
				continue;
			}

			obs->setTipoObstaculo(obtenerTipoObstaculo(tipoObstaculo));

			bool result = colocarCeldaEnMatriz(obs, listaElementos.at(i).getStartLine());

			if(!result)
			{
				//Logger no se pudo meter elemento porque ya está ocupada la posicion
				stringstream msg;
				msg << "En Grilla, no se pudo colocar el obstaculo; posicion ya ocupada. Linea:" << listaElementos.at(i).getStartLine();
				Logger::getInstance()->logWarning(msg.str());
			}
		}

		else
		{
			//Logger (tag con nombre incorrecto) y sigue
			stringstream msg;
			msg << "En Grilla, se ignora tag desconocido '" << listaElementos.at(i).getName() << "'. Linea: " << listaElementos.at(i).getStartLine();
			Logger::getInstance()->logWarning(msg.str());
		}
	}
}

bool Grilla::colocarCeldaEnMatriz(Celda* c, int linea)
{
	int fila = c->getFila();
	int columna = c->getColumna();

	if (fila > alto)
	{
		//Logger y valor por defecto
		stringstream msg;
		msg << "En Grilla, celda con fila mayor al alto de la grilla; no se agrega a matriz. Linea:" << linea;
		Logger::getInstance()->logWarning(msg.str());
		delete c;
		return false;
	}

	if (columna > ancho)
	{
		//Logger y valor por defecto
		stringstream msg;
		msg << "En Grilla, celda con columna mayor al ancho de la grilla; se asigna columna por defecto. Linea" << linea;
		Logger::getInstance()->logWarning(msg.str());
		delete c;
		return false;
	}

	if (matriz.at(fila).at(columna)->esOcupada())
	{
		delete c;
		return false;
	}

	Celda* celda = matriz.at(fila).getValueAt(columna);
	c->Ocupar();
	matriz.at(fila).at(columna) = c;
	delete celda;

	return true;
}

bool Grilla::verificarTipoBonusExistente(std::string tb)
{
	for (size_t i = 0; i < tiposBonus.length(); i++)
	{
		if (tb == tiposBonus.at(i).getNombre())
		{
			return true;
		}
	}

	return false;
}

bool Grilla::verificarTipoObstaculoExistente(std::string to)
{
	for(size_t i = 0; i < tiposObstaculos.length(); i++)
	{
		if (to == tiposObstaculos.at(i).getNombre())
		{
			return true;
		}
	}

	return false;
}

TipoBonus Grilla::obtenerTipoBonus(std::string tb)
{
	for(size_t i = 0; i < tiposBonus.length(); i++)
	{
		if (tb == tiposBonus.at(i).getNombre())
		{
			if (!tiposBonus.at(i).esUtilizado())
			{
				tiposBonus.at(i).utilizarTipo();
			}

			return tiposBonus.at(i);
		}
	}
}

TipoObstaculo Grilla::obtenerTipoObstaculo(std::string to)
{
	for(size_t i = 0; i < tiposObstaculos.length(); i++)
	{
		if (to == tiposObstaculos.at(i).getNombre())
		{
			if (!tiposObstaculos.at(i).esUtilizado())
			{
				tiposObstaculos.at(i).utilizarTipo();
			}

			return tiposObstaculos.at(i);
		}
	}
}

void Grilla::verificarTiposUtilizados()
{
	for (size_t i = 0; i < tiposBonus.length(); i++)
	{
		if(!tiposBonus.at(i).esUtilizado())
		{
			stringstream msg;
			msg << "El tipo bonus " << tiposBonus.at(i).getNombre() << " no está siendo utilizado. Linea: " << tiposBonus.at(i).getLinea();
			Logger::getInstance()->logWarning(msg.str());
		}
	}

	for (size_t i = 0; i < tiposObstaculos.length(); i++)
	{
		if(!tiposObstaculos.at(i).esUtilizado())
		{
			stringstream msg;
			msg << "El tipo obstaculo " << tiposObstaculos.at(i).getNombre() << " no está siendo utilizado. Linea: " << tiposObstaculos.at(i).getLinea();
			Logger::getInstance()->logWarning(msg.str());
		}
	}
}
 
Grilla::Grilla(const Grilla& other) : alto(other.alto), ancho(other.ancho),
 tipoObstaculoPorDefecto(other.tipoObstaculoPorDefecto), 
 tiposObstaculos(other.tiposObstaculos), 
 tiposBonus(other.tiposBonus), tieneError(other.tieneError)
{
	if (other.matrizGenerada)
	{
		for (size_t i = 0; i < this->alto; i++)
		{
			//agrego fila
			this->matriz.add(List<Celda*>());
			for (size_t j = 0; j < this->ancho; j++)
			{
				//lleno fila
				Celda* celda = other.matriz.at(i).at(j);
				this->matriz.at(i).add(celda->copiar());
			}	
		}

		this->matrizGenerada = true;
	}
}

Grilla& Grilla::operator=(const Grilla& other)
{
	if (this == &other) 
	{
		return *this;
	}

	if (this->matrizGenerada)
	{
		for (size_t i = this->alto - 1; i >= 0; i--)
		{
			for (size_t j = 0; j < this->ancho; j++)
			{
				//borro celda
				delete this->matriz.at(i).at(j);
			}	
			this->matriz.removeAt(i);
		}
	}

	this->alto = other.alto;
	this->ancho = other.ancho;
	this->tipoObstaculoPorDefecto = other.tipoObstaculoPorDefecto; 
	this->tiposObstaculos = other.tiposObstaculos;
	this->tiposBonus = other.tiposBonus;
	this->tieneError = other.tieneError;
	
	if (other.matrizGenerada)
	{
		for (size_t i = 0; i < this->alto; i++)
		{
			//agrego fila
			this->matriz.add(List<Celda*>());
			for (size_t j = 0; j < this->ancho; j++)
			{
				//lleno fila
				Celda* celda = other.matriz.at(i).at(j);
				this->matriz.at(i).add(celda->copiar());
			}	
		}

		this->matrizGenerada = true;
	}

	return *this;
}

void Grilla::populateValidAttributes(void)
{
	this->validAttributes.add("ancho");
	this->validAttributes.add("alto");
	this->validAttributes.add("tipoobstaculopordefecto");
}

bool Grilla::validateAttributes(XmlElement& e)
{
	List<XmlAttribute> attributes = e.getAttributes();

	for(size_t i = 0; i < attributes.length(); i++)
	{
		XmlAttribute att = attributes.at(i);
		
		if(!this->validAttributes.contains(att.getKey()))
		{
			stringstream msg;
			msg << "Clave de atributo: " << att.getKey() << " no es valida para la grilla. Linea: " << e.getStartLine();
			Logger::getInstance()->logError(msg.str());
			return false;
		}
	}

	return true;
}

bool Grilla::hasError(void)
{
	for(size_t i = 0; i < this->alto; i++)
	{
		for(size_t j = 0; j < this->ancho; j++)
		{
			if(this->getCelda(i, j)->hasError())
			{
				return true;
			}
		}
	}

	return this->tieneError;
}