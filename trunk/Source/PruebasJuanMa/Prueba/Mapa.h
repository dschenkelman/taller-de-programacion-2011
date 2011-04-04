#include <vector>
#include "Obstaculo.h"

using namespace System;
using namespace std;

class Mapa{
private:
	int ancho;
	int alto;
	vector<Obstaculo> listaObstaculos;

public:
	void agregarObstaculo(Obstaculo obstaculoNuevo);
	int cantidadObstaculos();
	void setAncho(int ancho);
	void setAlto(int alto);
	int getAncho();
	int getAlto();
};