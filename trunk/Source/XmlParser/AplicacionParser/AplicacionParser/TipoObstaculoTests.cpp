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
	printResult("testAtributoTexturaDeMasDeUnCaracterLoggeaWarning", testAtributoTexturaDeMasDeUnCaracterLoggeaWarning());
	printResult("testAtributoTexturaCorrectoGuardaCorrectamente", testAtributoTexturaCorrectoGuardaCorrectamente());

	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

void TipoObstaculoTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

bool TipoObstaculoTests::testAtributoTexturaDeMasDeUnCaracterLoggeaWarning()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("textura", "*+");
	elemento.addAttribute(atributo);

	// Obtengo el tamanio antes de crear el obstaculo
	size_t tamanioAntes = Logger::getInstance()->obtenerTamanioArchivo();

	// creo el obstaculo
	TipoObstaculo tipoObstaculo(elemento);

	// Tamanio despues de crear el obstaculo
	size_t tamanioDespues = Logger::getInstance()->obtenerTamanioArchivo();

	// finalizo el logger
	Logger::getInstance()->closeLog();

	return (tamanioAntes<tamanioDespues)?true:false;
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