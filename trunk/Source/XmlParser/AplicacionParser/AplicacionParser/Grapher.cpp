#include "stdafx.h"
#include "Grapher.h"
#include "Grilla.h"
#include "Window.h"
#include "Image.h"
#include <string>

using namespace std;

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

	Window w(escenario.getNombre(), windowHeight, windowWidth);
	Image texturaFondo(escenario.getTextura().getPath());
	
	//despues habria que agrandar para que ocupe todo el fondo
	w.display(texturaFondo, 0, 0);

	// va a truncar y es la idea. tiene que quedar mas chico porque sino,
	// no entran todas las celdas
	int imageHeight = windowHeight / grilla.getAlto();
	int imageWidth = windowWidth / grilla.getAncho();

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

			string path = celda->obtenerRepresentacion(celSup, celInf, celDer, celIzq);
			Image textura(path);
			w.display(textura, imageWidth * j, imageHeight * i);
			//delete celSup, celInf, celDer, celIzq;
		}
	}

	w.refresh();

	
	//esperar para cerrar
	SDL_Event e;
	bool running = true;
 
	while(running) 
	{
		while(SDL_PollEvent(&e)) 
		{
			switch(e.type)
			{
				case SDL_QUIT:
					running = false;
					w.close();
					break;
			}
		}
	}

}