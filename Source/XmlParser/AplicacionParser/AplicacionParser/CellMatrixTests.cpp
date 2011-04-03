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

void CellMatrixTests::run()
{
	//printResult("testListIsCreatedWithNoElements", testListIsCreatedWithNoElements());

	//dump memory leaks to VS Output Window
	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

CellMatrixTests::~CellMatrixTests(void)
{
}

