#include "StdAfx.h"
#include "TipoObstaculoTests.h"
#include <iostream>
#include <exception>
using namespace std;

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