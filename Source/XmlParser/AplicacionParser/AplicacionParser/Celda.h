#pragma once

class Celda
{
protected:
	size_t fila;
	size_t columna;
public:
	Celda(size_t f, size_t c);
	Celda(void);
	size_t getFila();
	size_t getColumna();
	~Celda(void);
};
