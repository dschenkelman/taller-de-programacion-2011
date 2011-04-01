#include "StdAfx.h"
#include "TipoObstaculoTests.h"
#include <iostream>
#include <exception>
using namespace std;
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


void TipoObstaculoTests::printLeaks(int leaks)
{
	std::cout << "List Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

TipoObstaculoTests::TipoObstaculoTests(void)
{
}

TipoObstaculoTests::~TipoObstaculoTests(void)
{
}

void TipoObstaculoTests::run(void)
{
	printResult("testAtributoTexturaDeMasDeUnCaracterTiraExcepcion", testAtributoTexturaDeMasDeUnCaracterTiraExcepcion());
	printResult("testAtributoTexturaCorrectoGuardaCorrectamente", testAtributoTexturaCorrectoGuardaCorrectamente());

	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

void TipoObstaculoTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

bool TipoObstaculoTests::testAtributoTexturaDeMasDeUnCaracterTiraExcepcion()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("textura", "*+");
	elemento.addAttribute(atributo);

	try
	{
		TipoObstaculo tipoObstaculo(elemento);
	}
	catch (exception& e)
	{
		return true;
	}

	return false;
}

bool TipoObstaculoTests::testAtributoTexturaCorrectoGuardaCorrectamente()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("textura", "+");
	elemento.addAttribute(atributo);

	TipoObstaculo tipoObstaculo(elemento);
	
	char textura = tipoObstaculo.getTextura();

	if (textura != '+')
	{
		return false;
	}

	return true;
}