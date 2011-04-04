#include "stdafx.h"
#include "Grapher.h"
#include "Grilla.h"
#include "Obstaculo.h"
#include "Camino.h"

Grapher::Grapher()
{
}

Grapher::~Grapher()
{
}

void Grapher::draw(Escenario& escenario)
{
	List<List<Celda*>> pMatriz = escenario.getGrilla().getMatriz();

	// Se muestra el nombre del Escenario
	std::cout << "Escenario: "+escenario.getNombre()+" \n";

	// Se dibuja fila por fila de la matriz
	for(unsigned int i=0; i<pMatriz.length(); i++)
	{
		for(unsigned int j=0; j<pMatriz.at(i).length(); j++)
		{
			// A cada celda le pido su representacion y la muestro por consola
			Celda* c = pMatriz.at(i).at(j);
			if(c->esOcupada())
			{
				Obstaculo* obs = dynamic_cast<Obstaculo*>(c);
				if (obs != 0)
				{
					std::cout << obs->obtenerRepresentacion();
				}
				else
				{
						Camino* cam = dynamic_cast<Camino*>(c);
						if (cam != 0)
						{
							std::cout << cam->obtenerRepresentacion();
						}
						else
						{
							std::cout << c->obtenerRepresentacion();
						}
				}
			}
			else
			{
				std::cout << "m";
			}
		}
		// Despues de imprimir la fila imprimo  un salto de linea
		std::cout << '\n';
	}
}