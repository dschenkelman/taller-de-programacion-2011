#include "stdafx.h"
#include "Grapher.h"
#include "Grilla.h"
#include "Window.h"
#include "Image.h"
#include <string>
#include "Logger.h"
#include <map>
#include <iostream>

using namespace std;

Grapher::Grapher() : windowHeight(480), windowWidth(640), imageCache()
{
	//default 640x480
}

Grapher::~Grapher()
{
	for (this->iter = this->imageCache.begin(); this->iter != this->imageCache.end(); this->iter++) {
		delete(iter->second);
	}
}

void Grapher::draw(Escenario& escenario)
{
	Image *imagePtr;
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
		//w.display(texturaFondo, 0, 0, 0, 0, 0, -1);
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
			
			Textura t = celda->obtenerTextura();
			string nombreTextura = t.getNombre();
			//Image imagen;
			if (this->imageCache.find(nombreTextura) == this->imageCache.end())
			{
				//not in cache
				imagePtr=celda->obtenerRepresentacion();
				imagePtr->resize(imageWidth, imageHeight);
				if (nombreTextura != ""){
					this->imageCache[nombreTextura] = imagePtr;
				}
			}
			else
			{
				imagePtr = (this->imageCache[nombreTextura]);
			}
			//imagen=*imagePtr;
			if (!(imagePtr->hasError()))
			{
				w.display((imagePtr), imageWidth * j, imageHeight * i, t.getRed(), t.getGreen(), t.getBlue(), t.getDelta());
			}
			else
			{
				//log
				Logger::getInstance()->logError(imagePtr->getErrorMessage());
				error = true;
			}
		}
	}

	if (!error)
	{
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
	else
	{
		cout << "Error al graficar. Ver el archivo parser.log.txt";
		w.close();
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