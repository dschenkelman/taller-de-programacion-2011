#include "StdAfx.h"
#include "GrapherTests.h"
#include "Grapher.h"
#include <iostream>
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

GrapherTests::GrapherTests(void)
{
}

GrapherTests::~GrapherTests(void)
{
}

void GrapherTests::printLeaks(int leaks)
{
	std::cout << "Escenario Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

void GrapherTests::run(void)
{
	printResult("testGraficarEscenario", testGraficarEscenario());
	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

void GrapherTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

bool GrapherTests::testGraficarEscenario(void)
{

	return true;
}