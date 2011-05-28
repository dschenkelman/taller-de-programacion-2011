#include "StdAfx.h"
#include "TipoBonusTests.h"
#include "Logger.h"
#include <exception>
#include <iostream>
using namespace std;
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void TipoBonusTests::printLeaks(int leaks)
{
	std::cout << "TipoBonus Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

TipoBonusTests::TipoBonusTests(void)
{
}

TipoBonusTests::~TipoBonusTests(void)
{
}

void TipoBonusTests::run(void)
{
	printResult("testAtributoTexturaCorrectoGuardaCorrectamente", testAtributoTexturaCorrectoGuardaCorrectamente());
	printResult("testNonValidAttributeMakesHasErrorTrue", testNonValidAttributeMakesHasErrorTrue());
	printResult("testCanUseStringAsTextura", testCanUseStringAsTextura());
	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

void TipoBonusTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

bool TipoBonusTests::testAtributoTexturaCorrectoGuardaCorrectamente()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("textura", "+");
	elemento.addAttribute(atributo);

	TipoBonus tipoBonus(elemento);
	
	std::string textura = tipoBonus.getNombreTextura();

	if (textura != "+")
	{
		return false;
	}

	return true;
}

bool TipoBonusTests::testNonValidAttributeMakesHasErrorTrue(void)
{
	XmlElement element("TipoBonus", 1, 2);
	XmlAttribute att1("nombre", "Pizza");
	XmlAttribute att2("textura", "Z");
	XmlAttribute att3("invalido", "invalido");

	element.addAttribute(att1);
	element.addAttribute(att2);
	element.addAttribute(att3);

	TipoBonus tipoBonus(element);

	bool successCondition = tipoBonus.hasError();

	Logger::closeLog();

	return successCondition;
}

bool TipoBonusTests::testCanUseStringAsTextura(void)
{
	XmlElement element("TipoBonus", 1, 2);
	XmlAttribute att1("nombre", "Pizza");
	XmlAttribute att2("textura", "PizzaGrande");

	element.addAttribute(att1);
	element.addAttribute(att2);

	TipoBonus tipoBonus(element);

	bool successCondition = tipoBonus.getNombreTextura() == "PizzaGrande";

	Logger::closeLog();

	return successCondition;
}