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
	printResult("testAtributoTexturaDeMasDeUnCaracterLoggeaWarning", testAtributoTexturaDeMasDeUnCaracterLoggeaWarning());
	printResult("testAtributoTexturaCorrectoGuardaCorrectamente", testAtributoTexturaCorrectoGuardaCorrectamente());
	printResult("testNonValidAttributeMakesHasErrorTrue", testNonValidAttributeMakesHasErrorTrue());
	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

void TipoBonusTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

bool TipoBonusTests::testAtributoTexturaDeMasDeUnCaracterLoggeaWarning()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("textura", "*+");
	elemento.addAttribute(atributo);

	// Obtengo el tamanio antes de crear el tipo bonus
	size_t tamanioAntes = Logger::getInstance()->obtenerTamanioArchivo();

	// creo el obstaculo
	TipoBonus tipoBonus(elemento);

	// Tamanio despues de crear el obstaculo
	size_t tamanioDespues = Logger::getInstance()->obtenerTamanioArchivo();

	// finalizo el logger
	Logger::getInstance()->closeLog();

	return (tamanioAntes<tamanioDespues)?true:false;
}

bool TipoBonusTests::testAtributoTexturaCorrectoGuardaCorrectamente()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("textura", "+");
	elemento.addAttribute(atributo);

	TipoBonus tipoBonus(elemento);
	
	char textura = tipoBonus.getTextura();

	if (textura != '+')
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