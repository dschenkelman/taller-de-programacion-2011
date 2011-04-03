#include "StdAfx.h"
#include "ObstaculoTests.h"
#include "Logger.h"
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
	printResult("testAtributoFilaConValorNegativoLoggeaError", testAtributoFilaConValorNegativoLoggeaError());
	printResult("testAtributoColumnaConValorNegativoLoggeaError", testAtributoColumnaConValorNegativoLoggeaError());
	printResult("testAtributoFilaCorrectoGuardaCorrectamente", testAtributoFilaCorrectoGuardaCorrectamente());
	printResult("testAtributoColumnaCorrectoGuardaCorrectamente",testAtributoColumnaCorrectoGuardaCorrectamente());

	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

void ObstaculoTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

bool ObstaculoTests::testAtributoFilaConValorNegativoLoggeaError()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("fila", "-5");
	elemento.addAttribute(atributo);
	
	// Obtengo el tamanio antes de crear el obstaculo
	size_t tamanioAntes = Logger::getInstance()->obtenerTamanioArchivo();

	// creo el obstaculo
	Obstaculo obstaculo(elemento);

	// Tamanio despues de crear el obstaculo
	size_t tamanioDespues = Logger::getInstance()->obtenerTamanioArchivo();

	// finalizo el logger
	Logger::getInstance()->closeLog();

	return (tamanioAntes<tamanioDespues)?true:false;
}

bool ObstaculoTests::testAtributoColumnaConValorNegativoLoggeaError()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("columna", "-9");
	elemento.addAttribute(atributo);

	// Obtengo el tamanio antes de crear el obstaculo
	size_t tamanioAntes = Logger::getInstance()->obtenerTamanioArchivo();

	// creo el obstaculo
	Obstaculo obstaculo(elemento);

	// Tamanio despues de crear el obstaculo
	size_t tamanioDespues = Logger::getInstance()->obtenerTamanioArchivo();
	
	// finalizo el logger
	Logger::getInstance()->closeLog();

	return (tamanioAntes<tamanioDespues)?true:false;
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