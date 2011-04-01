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
	printResult("testGenerarMatrizGeneraCorrectamente", testGenerarMatrizGeneraCorrectamente());
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

bool GrillaTests::testGenerarMatrizGeneraCorrectamente()
{
	XmlElement elementoGrilla("Grilla", 1, 1000);
	XmlAttribute atributoAlto("alto", "10");
	XmlAttribute atributoAncho("ancho", "10");
	XmlAttribute atributoTipo("tipoObstaculoPorDefecto", "obstaculoDef");
	elementoGrilla.addAttribute(atributoAlto);
	elementoGrilla.addAttribute(atributoAncho);
	elementoGrilla.addAttribute(atributoTipo);

	XmlElement elementoObstaculoUno("obstaculo", 2, 900);
	XmlAttribute atributoFilaO1("fila", "2");
	XmlAttribute atributoColumnaO1("columna", "9");
	elementoObstaculoUno.addAttribute(atributoFilaO1);
	elementoObstaculoUno.addAttribute(atributoColumnaO1);

	XmlElement elementoCaminoUno("camino", 3, 800);
	XmlAttribute atributoFilaC1("fila", "1");
	XmlAttribute atributoColumnaC1("columna", "5");
	elementoCaminoUno.addAttribute(atributoFilaC1);
	elementoCaminoUno.addAttribute(atributoColumnaC1);

	XmlElement elementoObstaculoDos("obstaculo", 2, 900);
	XmlAttribute atributoFilaO2("fila", "7");
	XmlAttribute atributoColumnaO2("columna", "4");
	elementoObstaculoDos.addAttribute(atributoFilaO2);
	elementoObstaculoDos.addAttribute(atributoColumnaO2);

	XmlElement elementoCaminoDos("camino", 3, 800);
	XmlAttribute atributoFilaC2("fila", "4");
	XmlAttribute atributoColumnaC2("columna", "6");
	elementoCaminoDos.addAttribute(atributoFilaC2);
	elementoCaminoDos.addAttribute(atributoColumnaC2);

	elementoGrilla.addChild(elementoCaminoUno);
	elementoGrilla.addChild(elementoCaminoDos);
	elementoGrilla.addChild(elementoObstaculoUno);
	elementoGrilla.addChild(elementoObstaculoDos);

	Grilla grilla(elementoGrilla);

	return true;
}