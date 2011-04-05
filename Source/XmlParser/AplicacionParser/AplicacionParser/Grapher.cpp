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
	List<List<Celda*>> pMatriz = escenario.getGrilla().getMatriz();

	// Se muestra el nombre del Escenario
	std::cout << "Escenario: "+escenario.getNombre()+" \n";

	// Se dibuja fila por fila de la matriz
	for(unsigned int i=0; i<pMatriz.length(); i++)
	{
		for(unsigned int j=0; j<pMatriz.at(i).length(); j++)
		{
			// A cada celda le pido su representacion y la muestro por consola
			Celda* celda = pMatriz.at(i).at(j);
			
			Celda* celSup = 0; 
			int posSup = i-1;
			if( posSup >= 0) 
				celSup = pMatriz.at(posSup).at(j);
			
			Celda* celInf = 0; 
			int posInf = i+1;
			if( posInf < pMatriz.length() ) 
				celInf = pMatriz.at(posInf).at(j);
			
			Celda* celDer = 0; 
			int posDer = j+1;
			if( posDer < pMatriz.at(i).length()) 
				celDer = pMatriz.at(i).at(posDer);
			
			Celda* celIzq = 0; 
			int posIzq = j-1;
			if( posIzq > 0) 
				celIzq = pMatriz.at(i).at(posIzq);


			if(celda->esOcupada()){
				std::cout << celda->obtenerRepresentacion(celSup, celInf, celDer, celIzq);
			}else{
				std::cout << " ";
			}

			//delete celSup, celInf, celDer, celIzq;
		}
		// Despues de imprimir la fila imprimo  un salto de linea
		std::cout << '\n';
	}
}