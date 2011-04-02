#include "StdAfx.h"
#include "CaminoTests.h"
using namespace std;

//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

CaminoTests::CaminoTests(void)
{
}

CaminoTests::~CaminoTests(void)
{
}

void CaminoTests::printLeaks(int leaks)
{
	std::cout << "Camino Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

void CaminoTests::run(void)
{
	printResult("testAtributoFilaConValorNegativoTiraExcepcion", testAtributoFilaConValorNegativoTiraExcepcion());
	printResult("testAtributoColumnaConValorNegativoTiraExcepcion", testAtributoColumnaConValorNegativoTiraExcepcion());
	printResult("testAtributoFilaCorrectoGuardaCorrectamente", testAtributoFilaCorrectoGuardaCorrectamente());
	printResult("testAtributoColumnaCorrectoGuardaCorrectamente",testAtributoColumnaCorrectoGuardaCorrectamente());
	printResult("testCaminoConBonusCreaCorrectamente", testCaminoConBonusCreaCorrectamente());
	printResult("testCaminoConDosBonusTiraExcepcion", testCaminoConDosBonusTiraExcepcion());

	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

void CaminoTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

bool CaminoTests::testAtributoFilaConValorNegativoTiraExcepcion()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("fila", "-5");
	elemento.addAttribute(atributo);

	try
	{
		Camino camino(elemento);
	}
	catch(exception& e)
	{
		return true;
	}
	
	Logger::getInstance()->closeLog();
	return false;
}

bool CaminoTests::testAtributoColumnaConValorNegativoTiraExcepcion()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("columna", "-9");
	elemento.addAttribute(atributo);

	try
	{
		Camino camino(elemento);
	}
	catch(exception& e)
	{
		return true;
	}
	
	Logger::getInstance()->closeLog();
	return false;
}

bool CaminoTests::testAtributoFilaCorrectoGuardaCorrectamente()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("fila", "9");
	elemento.addAttribute(atributo);

	Camino camino(elemento);

	int fila = camino.getFila();
	
	Logger::getInstance()->closeLog();
	if (fila != 9)
	{
		return false;
	}

	return true;
}

bool CaminoTests::testAtributoColumnaCorrectoGuardaCorrectamente()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("columna", "13");
	elemento.addAttribute(atributo);

	Camino camino(elemento);

	int columna = camino.getColumna();

	if (columna != 13)
	{
		return false;
	}

	return true;
}

bool CaminoTests::testCaminoConBonusCreaCorrectamente()
{
	XmlElement xmlElement("camino", 1, 100);
	XmlAttribute atributoFila("fila", "4");
	XmlAttribute atributoColumna("columna", "8");
	xmlElement.addAttribute(atributoFila);
	xmlElement.addAttribute(atributoColumna);

	XmlElement xmlElementBonus("bonus", 1, 20);
	XmlAttribute atributoTipo("tipo", "uva");
	xmlElementBonus.addAttribute(atributoTipo);

	xmlElement.addChild(xmlElementBonus);

	Camino camino(xmlElement);

	if(camino.getFila() != 4)
	{
		return false;
	}

	if(camino.getColumna() != 8)
	{
		return false;
	}

	if(camino.getBonus().getTipo() != "uva")
	{
		return false;
	}

	return true;
}

bool CaminoTests::testCaminoConDosBonusTiraExcepcion()
{
	XmlElement xmlElement("camino", 1, 100);
	XmlAttribute atributoFila("fila", "4");
	XmlAttribute atributoColumna("columna", "8");
	xmlElement.addAttribute(atributoFila);
	xmlElement.addAttribute(atributoColumna);

	XmlElement xmlElementBonusUno("bonus", 1, 20);
	XmlAttribute atributoTipoB1("tipo", "uva");
	xmlElementBonusUno.addAttribute(atributoTipoB1);

	XmlElement xmlElementBonusDos("bonus", 1, 20);
	XmlAttribute atributoTipoB2("tipo", "sandia");
	xmlElementBonusDos.addAttribute(atributoTipoB2);

	xmlElement.addChild(xmlElementBonusUno);
	xmlElement.addChild(xmlElementBonusDos);

	try
	{
		Camino camino(xmlElement);
	}
	catch(exception& e)
	{
		return true;
	}

	return false;
}