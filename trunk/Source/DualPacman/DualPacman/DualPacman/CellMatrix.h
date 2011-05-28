#pragma once
#include "Celda.h"

class CellMatrix
{
public:
	CellMatrix(int width, int height);
	int getWidth();
	int getHeight();
	bool insert(Celda c);
	bool getCelda(int row, int column, Celda* c);
	~CellMatrix(void);
private:
	int width, height;
	Celda *cells;
};
