#include "StdAfx.h"
#include "TipoObstaculoTests.h"
#include "Logger.h"
#include <iostream>
#include <exception>
using namespace std;
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


void TipoObstaculoTests::printLeaks(int leaks)
{
	std::cout << "TipoObstaculo Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

TipoObstaculoTests::TipoObstaculoTests(void)
{
}

TipoObstaculoTests::~TipoObstaculoTests(void)
{
}

void TipoObstaculoTests::run(void)
{
	printResult("testAtributoTexturaCorrectoGuardaCorrectamente", testAtributoTexturaCorrectoGuardaCorrectamente());
	printResult("testNonValidAttributeMakesHasErrorTrue", testNonValidAttributeMakesHasErrorTrue());
	printResult("testCanUseStringAsTextura", testCanUseStringAsTextura());

	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

void TipoObstaculoTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

bool TipoObstaculoTests::testAtributoTexturaCorrectoGuardaCorrectamente()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("textura", "+");
	elemento.addAttribute(atributo);

	TipoObstaculo tipoObstaculo(elemento);
	
	string textura = tipoObstaculo.getNombreTextura();

	if (textura != "+")
	{
		return false;
	}

	return true;
}

bool TipoObstaculoTests::testNonValidAttributeMakesHasErrorTrue(void)
{
	XmlElement element("TipoObstaculo", 1, 2);
	XmlAttribute att1("nombre", "Piedra");
	XmlAttribute att2("textura", "P");
	XmlAttribute att3("invalido", "invalido");

	element.addAttribute(att1);
	element.addAttribute(att2);
	element.addAttribute(att3);

	TipoObstaculo tipoObstaculo(element);

	bool successCondition = tipoObstaculo.hasError();

	Logger::closeLog();

	return successCondition;
}

bool TipoObstaculoTests::testCanUseStringAsTextura(void)
{
	XmlElement element("TipoObstaculo", 1, 2);
	XmlAttribute att1("nombre", "Piedra");
	XmlAttribute att2("textura", "PiedraGrande");

	element.addAttribute(att1);
	element.addAttribute(att2);

	TipoObstaculo tipoObstaculo(element);

	bool successCondition = tipoObstaculo.getNombreTextura() == "PiedraGrande";

	Logger::closeLog();

	return successCondition;
}