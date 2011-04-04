#include "stdafx.h"
#include "Grapher.h"
#include "Grilla.h"

Grapher::Grapher()
{
}

Grapher::~Grapher()
{
}

void Grapher::draw(Escenario escenario)
{
	Grilla pGrid = escenario.getGrilla();

	List<List<Celda>> pMatriz = pGrid.getMatriz();

	// Se muestra el nombre del Escenario
	std::cout << "Escenario: "+escenario.getNombre()+" \n";

	// Se dibuja fila por fila de la matriz
	for(unsigned int i=0; i<pMatriz.length(); i++)
	{
		for(unsigned int j=0; j<pMatriz.at(i).length(); j++)
		{
			// A cada celda le pido su textura y la muestro por consola
			Celda cel = pMatriz.at(i).at(j);
			if(pMatriz.at(i).at(j).esOcupada())
			{
				std::cout << cel.obtenerRepresentacion();
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