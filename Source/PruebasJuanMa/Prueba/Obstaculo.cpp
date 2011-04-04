#include "stdafx.h"
#include "Obstaculo.h"

Obstaculo::Obstaculo(void)
{
}

Obstaculo::~Obstaculo(void)
{
}

void Obstaculo::setNombre(std::string nombre){
	this->nombre = nombre;
}

std::string Obstaculo::getNombre(){
	return this->nombre;
}

std::string Obstaculo::obtenerRepresentacion(void)
{
	return "o";
}