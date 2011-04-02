#pragma once

class Celda
{
protected:
	int fila;
	int columna;
	bool ocupada;
public:
	Celda(int f, int c);
	Celda(void);
	int getFila();
	int getColumna();
	bool esOcupada();
	void Ocupar();
	~Celda(void);
};
