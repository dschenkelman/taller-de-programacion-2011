#include "StdAfx.h"
#include "CellMatrixTests.h"
#include <iostream>
#include <exception>
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

CellMatrixTests::CellMatrixTests(void)
{
}

void CellMatrixTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

void CellMatrixTests::printLeaks(int leaks)
{
	std::cout << "CellMatrixTests: Hubo " << leaks << " memory leaks." << endl << endl;
}

bool CellMatrixTests::testCellMatrixWithNoElements() {
	CellMatrix matrix(10,20);
	Celda celda;
	if (matrix.getCelda(1,1,&celda)) {
		return false;
	}
	return true;
}

bool CellMatrixTests::testReturnCorrectCell() {
	CellMatrix matrix(15,5);
	Celda c(3,2);
	matrix.insert(c);
	Celda d;
	return matrix.getCelda(3,2,&d);
}

void CellMatrixTests::run()
{
	printResult("testCellMatrixWithNoElements", testCellMatrixWithNoElements());
	printResult("testReturnCorrectCell", testReturnCorrectCell());

	//dump memory leaks to VS Output Window
	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

CellMatrixTests::~CellMatrixTests(void)
{
}

