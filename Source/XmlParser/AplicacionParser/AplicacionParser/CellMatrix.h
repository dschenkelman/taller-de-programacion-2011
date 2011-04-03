#pragma once
#include "Celda.h"

class CellMatrix
{
public:
	CellMatrix(int width, int height);
	bool insert(Celda c);
	bool getCelda(int row, int column, Celda* c);
	~CellMatrix(void);
private:
	int width, height;
	Celda **rows;
};
