#include "stdafx.h"
#include "Grapher.h"
#include "Grilla.h"
#include "Window.h"
#include "Image.h"
#include <string>
#include "Logger.h"
#include <map>

using namespace std;

Grapher::Grapher() : windowHeight(480), windowWidth(640), imageCache()
{
	//default 640x480
}

Grapher::~Grapher()
{
}

void Grapher::draw(Escenario& escenario)
{
	bool error = false;
	Grilla& grilla = escenario.getGrilla();

	// Se muestra el nombre del Escenario
	std::cout << "Escenario: "+escenario.getNombre()+" \n";

	Window w(escenario.getNombre(), windowHeight, windowWidth);
	Image texturaFondo(escenario.getTextura().getPath());
		
	if (!texturaFondo.hasError())
	{
		//despues habria que agrandar para que ocupe todo el fondo
		Textura t = escenario.getTextura();
		texturaFondo.crop(t.getTop(), t.getLeft(), t.getRight(), t.getBottom());
		Uint32 alphaPixel = t.getRed() | t.getGreen() << 8 | t.getBlue() << 16;
		texturaFondo.rotate(t.getRotation(), alphaPixel);
		texturaFondo.resize(windowWidth, windowHeight);
		w.display(texturaFondo, 0, 0, 0, 0, 0, -1);
	}
	else
	{
		error = true;
		Logger::getInstance()->logError(texturaFondo.getErrorMessage());
	}

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

			Textura t = celda->obtenerTextura(celSup, celInf, celDer, celIzq);
			string nombreTextura = t.getNombre();
			Image imagen;
			if (this->imageCache.find(nombreTextura) == this->imageCache.end())
			{
				//not in cache
				imagen = celda->obtenerRepresentacion(celSup, celInf, celDer, celIzq);
				imagen.resize(imageWidth, imageHeight);
				if (nombreTextura != "")
				{
					this->imageCache[nombreTextura] = imagen;
				}
			}
			else
			{
				imagen = this->imageCache[nombreTextura];
			}
			
			if (!imagen.hasError())
			{
				w.display(imagen, imageWidth * j, imageHeight * i, t.getRed(), t.getGreen(), t.getBlue(), t.getDelta());
			}
			else
			{
				//log
				Logger::getInstance()->logError(imagen.getErrorMessage());
				error = true;
			}
		}
	}

	if (!error)
	{
		w.refresh();
	}
	
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

void  Grapher::setVideoMode(int mode){

	switch(mode){
		case 640:{
			this->windowHeight=480;
			this->windowWidth=640;
			break;
		}
		case 800:{
			this->windowHeight=600;
			this->windowWidth=800;
			break;
				 }
		case 1024:{
			this->windowHeight=768;
			this->windowWidth=1024;
			break;
	    }
		default:{
			this->windowHeight=480;
			this->windowWidth=640;
		}
	}		


}
int  Grapher::getVideoMode(void){
	return this->windowWidth;
}