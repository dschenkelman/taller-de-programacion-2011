#include "StdAfx.h"
#include "CellMatrix.h"
#include "Celda.h"

CellMatrix::CellMatrix(int width, int height)
{
	this->cells = new Celda[width*height];
	this->width = width;
	this->height = height;
}

int CellMatrix::getWidth()
{
	return this->width;
}

int CellMatrix::getHeight()
{
	return this->height;
}

bool CellMatrix::insert(Celda c)
{
	int row = c.getFila();
	int column = c.getColumna();
	if (row > height || column > width) {
		return false;
	}
	this->cells[row*this->getWidth()+column] = c;
	return true;
}

bool CellMatrix::getCelda(int row, int column, Celda* c)
{
	if (row > height || column > width) {
		return false;
	}
	Celda obt = this->cells[row*this->getWidth()+column];
	if (!obt.esOcupada()) {
		return false;
	}
	*c = obt;
	return true;
}

CellMatrix::~CellMatrix(void)
{
	delete []cells;
}
