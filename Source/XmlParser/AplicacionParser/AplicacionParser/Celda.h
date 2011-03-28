#pragma once

class Celda
{
protected:
	int fila;
	int columna;
public:
	Celda(int f, int c);
	Celda(void);
	int getFila();
	int getColumna();
	~Celda(void);
};
