#include "stdafx.h"
#include "Grapher.h"
#include "Grilla.h"

Grapher::Grapher()
{
}

Grapher::~Grapher()
{
}

void Grapher::draw(Escenario& escenario)
{
	Grilla& grilla = escenario.getGrilla();

	// Se muestra el nombre del Escenario
	std::cout << "Escenario: "+escenario.getNombre()+" \n";

	// Se dibuja fila por fila de la matriz
	for(unsigned int i=0; i<grilla.getAlto(); i++)
	{
		for(unsigned int j=0; j<grilla.getAncho(); j++)
		{
			// A cada celda le pido su representacion y la muestro por consola
			Celda* celda = grilla.getCelda(i, j);
			
			Celda* celSup = 0; 
			int posSup = i-1;
			if( posSup >= 0) 
				celSup = grilla.getCelda(posSup, j);
			
			Celda* celInf = 0; 
			int posInf = i+1;
			if( posInf < grilla.getAlto() ) 
				celInf = grilla.getCelda(posInf, j);
			
			Celda* celDer = 0; 
			int posDer = j+1;
			if( posDer < grilla.getAncho()) 
				celDer = grilla.getCelda(i, posDer);
			
			Celda* celIzq = 0; 
			int posIzq = j-1;
			if( posIzq > 0) 
				celIzq = grilla.getCelda(i, posIzq);


			std::cout << celda->obtenerRepresentacion(celSup, celInf, celDer, celIzq);

			//delete celSup, celInf, celDer, celIzq;
		}
		// Despues de imprimir la fila imprimo  un salto de linea
		std::cout << '\n';
	}
}