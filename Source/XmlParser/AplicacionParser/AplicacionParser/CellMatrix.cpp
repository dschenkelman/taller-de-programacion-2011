#include "StdAfx.h"
#include "CellMatrix.h"
#include "Celda.h"

CellMatrix::CellMatrix(int width, int height)
{
	for (int i=0;i<height;i++) {
		this->rows[i] = new Celda[];
	}
	this->width = width;
	this->height = height;
}

bool CellMatrix::insert(Celda c)
{
	int row = c.getFila();
	int column = c.getColumna();
	if (row > height || column > width) {
		return false;
	}
	this->rows[row][column] = c;
	return true;
}

bool CellMatrix::getCelda(int row, int column, Celda* c)
{
	if (row > height || column > width) {
		return false;
	}
	*c = this->rows[row][column];
	return true;
}

CellMatrix::~CellMatrix(void)
{
}
