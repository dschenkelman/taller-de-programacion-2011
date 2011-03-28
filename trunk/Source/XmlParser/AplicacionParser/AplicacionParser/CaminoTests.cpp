#include "StdAfx.h"
#include "CaminoTests.h"
using namespace std;

CaminoTests::CaminoTests(void)
{
}

CaminoTests::~CaminoTests(void)
{
}

void CaminoTests::run(void)
{
	printResult("testAtributoFilaConValorNegativoTiraExcepcion", testAtributoFilaConValorNegativoTiraExcepcion());
	printResult("testAtributoColumnaConValorNegativoTiraExcepcion", testAtributoColumnaConValorNegativoTiraExcepcion());
	printResult("testAtributoFilaCorrectoGuardaCorrectamente", testAtributoFilaCorrectoGuardaCorrectamente());
	printResult("testAtributoColumnaCorrectoGuardaCorrectamente",testAtributoColumnaCorrectoGuardaCorrectamente());
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

	return false;
}

bool CaminoTests::testAtributoFilaCorrectoGuardaCorrectamente()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("fila", "9");
	elemento.addAttribute(atributo);

	Camino camino(elemento);

	int fila = camino.getFila();

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