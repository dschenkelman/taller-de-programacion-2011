#include "stdafx.h"
#include "Mapa.h"

void Mapa::agregarObstaculo(Obstaculo obstaculoNuevo){
	this->listaObstaculos.push_back(obstaculoNuevo);
}

int Mapa::cantidadObstaculos(){
	return this->listaObstaculos.size();
}

void Mapa::setAlto(int alto){
	this->alto = alto;
}

void Mapa::setAncho(int ancho){
	this->ancho = ancho;
}

int Mapa::getAlto(){
	return this->alto;
}

int Mapa::getAncho(){
	return this->ancho;
}