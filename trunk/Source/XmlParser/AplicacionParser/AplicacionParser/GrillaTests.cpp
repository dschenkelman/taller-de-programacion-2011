#include "StdAfx.h"
#include "GrillaTests.h"
#include <exception>
#include <iostream>
using namespace std;

GrillaTests::GrillaTests(void)
{
}

GrillaTests::~GrillaTests(void)
{
}

void GrillaTests::run(void)
{
	printResult("testAtributoAnchoConValorNegativoTiraExcepcion", testAtributoAnchoConValorNegativoTiraExcepcion());
	printResult("testAtributoAltoConValorNegativoTiraExcepcion", testAtributoAltoConValorNegativoTiraExcepcion());
	printResult("testAtributoAltoCorrectoGuardaCorrectamente", testAtributoAltoCorrectoGuardaCorrectamente());
	printResult("testAtributoAnchoCorrectoGuardaCorrectamente", testAtributoAnchoCorrectoGuardaCorrectamente());
}

void GrillaTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

bool GrillaTests::testAtributoAnchoConValorNegativoTiraExcepcion()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("ancho", "-4");
	elemento.addAttribute(atributo);

	try
	{
		Grilla grilla(elemento);
	}
	catch(exception& e)
	{
		return true;
	}

	return false;
}

bool GrillaTests::testAtributoAltoConValorNegativoTiraExcepcion()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("alto", "-6");
	elemento.addAttribute(atributo);

	try
	{
		Grilla grilla(elemento);
	}
	catch(exception& e)
	{
		return true;
	}

	return false;
}

bool GrillaTests::testAtributoAltoCorrectoGuardaCorrectamente()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("alto", "10");
	elemento.addAttribute(atributo);

	Grilla grilla(elemento);

	int alto = grilla.getAlto();

	if(alto != 10)
	{
		return false;
	}

	return true;
}

bool GrillaTests::testAtributoAnchoCorrectoGuardaCorrectamente()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("ancho", "8");
	elemento.addAttribute(atributo);

	Grilla grilla(elemento);

	int ancho = grilla.getAncho();

	if(ancho != 8)
	{
		return false;
	}

	return true;
}