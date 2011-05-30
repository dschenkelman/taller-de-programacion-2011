#include "StdAfx.h"
#include "Camino.h"
#include "List.h"
#include <sstream>
#include "Image.h"

using namespace std;

Camino::Camino(int f, int c) : Celda(f, c), tieneBonus(false), tieneError(false)
{
	this->populateValidAttributes();
	this->imagen=NULL;
}

Camino::Camino(XmlElement& e) : tieneBonus(false), tieneError(false)
{
	this->imagen=NULL;
	this->populateValidAttributes();
	this->tieneError = !this->validateAttributes(e);

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
			stringstream msg;
			msg << "En Camino, la cantidad de bonus es mayor a uno. Linea: " << e.getStartLine();
			Logger::getInstance()->logWarning(msg.str());
		}
	}
}

Camino::Camino(void)
{
	this->imagen=NULL;
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
	/*if (this->imagen != NULL)
	{
		EL CAMINO NO BORRA SUS IMAGENES PORQUE EL CACHE LO HACE POR EL
		delete(this->imagen);
	}*/
}

Image* Camino::obtenerRepresentacion()
{
	if (this->imagen == NULL)
	{
		this->imagen = new Image("Images/texturas/camino.bmp");

		if (this->hasBonus() && !(this->imagen->hasError()))
		{
			/*std::stringstream ss;
			std::string repres;*/
			TipoBonus tb = this->getBonus().getTipoBonus();
			int red = tb.getTextura().getRed();
			int green = tb.getTextura().getGreen();
			int blue = tb.getTextura().getBlue();
			this->imagen->superImpose(*(this->getBonus().obtenerRepresentacion()), red, green, blue, tb.getTextura().getDelta());
			/*ss >> repres;*/
		}
	}

	return this->imagen;
}


Image* Camino::borrarBonus()
{
	if (this->hasBonus() && !(this->imagen->hasError()))
	{
		Image imagen("Images/texturas/camino.bmp");
		TipoBonus tb = this->getBonus().getTipoBonus();
		int red = tb.getTextura().getRed();
		int green = tb.getTextura().getGreen();
		int blue = tb.getTextura().getBlue();
		this->imagen->superImpose(imagen, red, green, blue, tb.getTextura().getDelta());
		/*ss >> repres;*/
	}
	return this->imagen;
}

Camino::Camino(const Camino& other)
{

}

Celda* Camino::copiar(void)
{
	Camino* camino = new Camino(this->fila, this->columna);
	camino->ocupada = this->ocupada;
	camino->tieneBonus = this->tieneBonus;
	camino->bonus = this->bonus;
	camino->tieneError = this->tieneError;
	return camino;
}

bool Camino::hasError(void)
{
	bool bonusError = false;
	if (this->tieneBonus)
	{
		bonusError = this->bonus.hasError();
	}
	return this->tieneError || bonusError;
}

bool Camino::validateAttributes(XmlElement& e)
{
	List<XmlAttribute> attributes = e.getAttributes();
	size_t len = attributes.length();

	for (size_t i = 0; i < len; i++)
	{
		XmlAttribute att = attributes[i];
		if (!this->validAttributes.contains(att.getKey()))
		{
			stringstream msg;
			msg << "Clave de atributo: " << att.getKey() << " no es válida para el Camino. Linea: " << e.getStartLine();
			Logger::getInstance()->logError(msg.str());
			return false;
		}
	}

	return true;
}

void Camino::populateValidAttributes(void)
{
	this->validAttributes.add("fila");
	this->validAttributes.add("columna");
}

Textura Camino::obtenerTextura()
{
	Textura textura;
	textura.setNombre("Images/texturas/camino.bmp");
	
	if (this->hasBonus())
	{
		string nombreTexturaBonus = this->getBonus().getTipoBonus().getTextura().getNombre();
		textura.setNombre(textura.getNombre() + nombreTexturaBonus);
	}

	return textura;
}
void Camino::removeBonus(void){
	this->tieneBonus=false;
}