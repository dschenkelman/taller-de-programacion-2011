// Prueba.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include <stdio.h>
#include <string> 
#include <iostream> 
#include <sstream>
#include "XMLParser.h"
#include "Obstaculo.h"
#include "Celda.h"
#include "Camino.h"
#include "Mapa.h"
#include "ScreenLogger.h"

using namespace std;
using namespace System;

int main(array<System::String ^> ^args)
{
	XMLParser parser;

	Mapa mapaNuevo;

	// Prueba polimorfismo
	Celda listaCeldas[5];
	
	Camino cam1;
	listaCeldas[0] = cam1;
	
	Obstaculo obs1;
	listaCeldas[1] = obs1;
	
	Camino cam2;
	listaCeldas[2] = cam2;
	
	Obstaculo obs2;
	listaCeldas[3] = obs2;
	
	Camino cam3;
	listaCeldas[4] = cam3;

	for(int i=0; i<5; i++)
	{
		Celda* c = &(listaCeldas[i]);
		Obstaculo* obs = dynamic_cast<Obstaculo*>(c);
		if (obs != 0){
			std::cout << obs->obtenerRepresentacion();
		}else{
			Camino* cam = dynamic_cast<Camino*>(c);
			if (cam != 0){
				std::cout << cam->obtenerRepresentacion();
			}else{
				std::cout << c->obtenerRepresentacion();
			}
		}
		
	}
	std::cout << '\n';



	// Prueba del logger
	ScreenLogger* logger = ScreenLogger::getInstance();
	
	istringstream buffer(parser.parsear("ancho"));
	int ancho_int;
	buffer >> ancho_int;
	
	mapaNuevo.setAncho(ancho_int);

	istringstream buffer2(parser.parsear("alto"));
	int alto_int;
	buffer2 >> alto_int;
	mapaNuevo.setAlto(alto_int);
	
	//cout << "ancho: ";
	logger->logIn("ancho: ");

	cout << mapaNuevo.getAncho();
	cout << "\nalto: ";
	cout << mapaNuevo.getAlto();
    cout << "\nHola a todos\n";
	Console::Read();
    return 0;
}
