#include "StdAfx.h"
#include "Camino.h"
#include "List.h"
#include <sstream>

Camino::Camino(int f, int c) : Celda(f, c), tieneBonus(false)
{
}

Camino::Camino(XmlElement& e)
{
	if (e.hasAttribute("fila"))
	{
		std::string filaString = e.getValue("fila"); 
		int f = atoi(filaString.c_str());

		if (f < 0)
		{
			// Loggeo como Error que la fila sea menor a cero
			std::stringstream nroLinea;	nroLinea << e.getStartLine();
			Logger::getInstance()->logError("Línea " + nroLinea.str() + " -> En Camino, fila menor a cero.");
		}

		fila = f;
	}

	if(e.hasAttribute("columna"))
	{
		std::string columnaString = e.getValue("columna");
		int c = atoi(columnaString.c_str());

		if (c < 0)
		{
			// Loggeo como Error que la columna sea menor a cero
			std::stringstream nroLinea;	nroLinea << e.getStartLine();
			Logger::getInstance()->logError("Línea " + nroLinea.str() + " -> En Camino, columna menor a cero.");
		}

		columna = c;
	}

	tieneBonus = false;

	if (e.hasChildren())
	{
		List<XmlElement> listaHijos = e.getChildren();
		
		if(listaHijos.length() == 1)
		{
			Bonus b = Bonus(listaHijos.at(0));
			bonus = b;
			tieneBonus = true;
		}

		else
		{
			//un camino con más de un bonus, por ahi hay que meter advertencia y usar un solo bonus
			std::stringstream nroLinea;	nroLinea << e.getStartLine();
			Logger::getInstance()->logWarning("Línea "+nroLinea.str()+" -> En Camino, la cantidad de bonus es mayor a uno.");
		}
	}
}

Camino::Camino(void)
{
}

bool Camino::hasBonus()
{
	return tieneBonus;
}

Bonus& Camino::getBonus()
{
	return bonus;
}

Camino::~Camino(void)
{
}

std::string Camino::obtenerRepresentacion(Celda* celSup, Celda* celInf, Celda* celDer, Celda* celIzq)
{
	if (this->hasBonus())
	{
		/*std::stringstream ss;
		std::string repres;*/
		char rep[] = {this->getBonus().getTipoBonus().getTextura(), '\0'};
		return std::string(rep); 
		/*ss >> repres;*/
	}
	
	std::string repres = "+";
	// Intento castear las celdas 
	Camino* camSup = dynamic_cast<Camino*>(celSup);
	Camino* camInf = dynamic_cast<Camino*>(celInf);
	Camino* camDer = dynamic_cast<Camino*>(celDer);
	Camino* camIzq = dynamic_cast<Camino*>(celIzq);
	
	// Ningun vecino es un camino
	if( camSup == 0 && camInf == 0 && camDer == 0 && camIzq == 0 ){
		return ".";
	}
	
	// Solo vecinos superior o inferior son caminos
	if(( camSup != 0 || camInf != 0 )&&( camDer == 0 && camIzq == 0 )){
		return"|";
	}

	// Solo vecinos derecho o izquierdo son caminos
	if(( camDer != 0 || camIzq != 0 )&&( camSup == 0 && camInf == 0 )){
		return "-";
	}

	return repres;
}

Celda* Camino::copiar(void)
{
	Camino* camino = new Camino(this->fila, this->columna);
	camino->ocupada = this->ocupada;
	camino->tieneBonus = this->tieneBonus;
	camino->bonus = this->bonus;
	return camino;
}
