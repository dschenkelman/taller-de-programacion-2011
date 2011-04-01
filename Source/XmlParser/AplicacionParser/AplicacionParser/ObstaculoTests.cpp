#include "StdAfx.h"
#include "ObstaculoTests.h"
using namespace std;
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void ObstaculoTests::printLeaks(int leaks)
{
	std::cout << "Obstaculo Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

ObstaculoTests::ObstaculoTests(void)
{
}

ObstaculoTests::~ObstaculoTests(void)
{
}

void ObstaculoTests::run(void)
{
	printResult("testAtributoFilaConValorNegativoTiraExcepcion", testAtributoFilaConValorNegativoTiraExcepcion());
	printResult("testAtributoColumnaConValorNegativoTiraExcepcion", testAtributoColumnaConValorNegativoTiraExcepcion());
	printResult("testAtributoFilaCorrectoGuardaCorrectamente", testAtributoFilaCorrectoGuardaCorrectamente());
	printResult("testAtributoColumnaCorrectoGuardaCorrectamente",testAtributoColumnaCorrectoGuardaCorrectamente());

	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

void ObstaculoTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

bool ObstaculoTests::testAtributoFilaConValorNegativoTiraExcepcion()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("fila", "-5");
	elemento.addAttribute(atributo);

	try
	{
		Obstaculo obstaculo(elemento);
	}
	catch(exception& e)
	{
		return true;
	}

	return false;
}

bool ObstaculoTests::testAtributoColumnaConValorNegativoTiraExcepcion()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("columna", "-9");
	elemento.addAttribute(atributo);

	try
	{
		Obstaculo obstaculo(elemento);
	}
	catch(exception& e)
	{
		return true;
	}

	return false;
}

bool ObstaculoTests::testAtributoFilaCorrectoGuardaCorrectamente()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("fila", "9");
	elemento.addAttribute(atributo);

	Obstaculo obstaculo(elemento);

	int fila = obstaculo.getFila();

	if (fila != 9)
	{
		return false;
	}

	return true;
}

bool ObstaculoTests::testAtributoColumnaCorrectoGuardaCorrectamente()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("columna", "13");
	elemento.addAttribute(atributo);

	Obstaculo obstaculo(elemento);

	int columna = obstaculo.getColumna();

	if (columna != 13)
	{
		return false;
	}

	return true;
}