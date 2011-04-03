#include "stdafx.h"
#include "Grapher.h"
#include "Grilla.h"

Grapher::Grapher()
{
}

Grapher::~Grapher()
{
}

void Grapher::draw(Grilla &grid)
{
	Grilla* pGrid = NULL;
	*pGrid = grid;
	List<List<Celda>> pMatriz = pGrid->getMatriz();

	// Se muestra el nombre del Escenario
	std::cout << "Nombre escenario: \n";

	// Se dibuja fila por fila de la matriz
	for(unsigned int i=0; i<pMatriz.length(); i++)
	{
		for(unsigned int j=0; j<pMatriz.length(); i++)
		{
			// A cada celda le pido su textura y la muestro por consola
			//std::cout << pMatriz.at(j).at(i).getRepresentacion();
		}
		// Despues de imprimir la fila imprimo  un salto de linea
		std::cout << '\n';
	}
}