#include "StdAfx.h"
#include "GrillaTests.h"
#include <exception>
#include <iostream>
using namespace std;
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


void GrillaTests::printLeaks(int leaks)
{
	std::cout << "Grilla Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

GrillaTests::GrillaTests(void)
{
}

GrillaTests::~GrillaTests(void)
{
}

void GrillaTests::run(void)
{
	printResult("testAtributoAnchoConValorNegativoTomaValorPorDefecto", testAtributoAnchoConValorNegativoTomaValorPorDefecto());
	printResult("testAtributoAltoConValorNegativoTomaValorPorDefecto", testAtributoAltoConValorNegativoTomaValorPorDefecto());
	printResult("testAtributoAltoCorrectoGuardaCorrectamente", testAtributoAltoCorrectoGuardaCorrectamente());
	printResult("testAtributoAnchoCorrectoGuardaCorrectamente", testAtributoAnchoCorrectoGuardaCorrectamente());
	printResult("testGenerarMatrizGeneraCorrectamente", testGenerarMatrizGeneraCorrectamente());
	printResult("testTipoBonusInvalidoNoSeAgregaALaMatriz", testTipoBonusInvalidoNoSeAgregaALaMatriz());

	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

void GrillaTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

bool GrillaTests::testAtributoAnchoConValorNegativoTomaValorPorDefecto()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("ancho", "-4");
	elemento.addAttribute(atributo);

	List<TipoObstaculo> lo;
	List<TipoBonus> lb;

	Grilla grilla(elemento, lo, lb);
	Logger::getInstance()->closeLog();

	return (grilla.getAncho() == defGridAncho) ? true:false;
}

bool GrillaTests::testAtributoAltoConValorNegativoTomaValorPorDefecto()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("alto", "-6");
	elemento.addAttribute(atributo);

	List<TipoObstaculo> lo;
	List<TipoBonus> lb;

	Grilla grilla(elemento, lo, lb);

	Logger::getInstance()->closeLog();
	
	return (grilla.getAlto() == defGridAlto) ? true:false;
}

bool GrillaTests::testAtributoAltoCorrectoGuardaCorrectamente()
{
	XmlElement elemento("Nombre", 1, 100);
	XmlAttribute atributo("alto", "10");
	elemento.addAttribute(atributo);

	List<TipoObstaculo> lo;
	List<TipoBonus> lb;

	Grilla grilla(elemento, lo, lb);

	int alto = grilla.getAlto();
	Logger::getInstance()->closeLog();
	
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

	List<TipoObstaculo> lo;
	List<TipoBonus> lb;

	Grilla grilla(elemento, lo, lb);

	int ancho = grilla.getAncho();
	
	Logger::getInstance()->closeLog();
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

	List<TipoObstaculo> lo;
	List<TipoBonus> lb;

	Grilla grilla(elementoGrilla, lo, lb);

	List<List<Celda>> matrizObtenida = grilla.getMatriz();

	int prueba = matrizObtenida.at(2).at(9).getFila();

	Logger::getInstance()->closeLog();

	if (matrizObtenida.at(2).at(9).getFila() != 2 || matrizObtenida.at(2).at(9).getColumna() != 9)
	{
		return false;
	}

	if (matrizObtenida.at(1).at(5).getFila() != 1 || matrizObtenida.at(1).at(5).getColumna() != 5)
	{
		return false;
	}

	if (matrizObtenida.at(7).at(4).getFila() != 7 || matrizObtenida.at(7).at(4).getColumna() != 4)
	{
		return false;
	}

	if (matrizObtenida.at(4).at(6).getFila() != 4 || matrizObtenida.at(4).at(6).getColumna() != 6)
	{
		return false;
	}

	return true;
}

bool GrillaTests::testTipoBonusInvalidoNoSeAgregaALaMatriz()
{
	XmlElement elementoGrilla("Grilla", 1, 1000);
	XmlAttribute atributoAlto("alto", "10");
	XmlAttribute atributoAncho("ancho", "10");
	XmlAttribute atributoTipo("tipoObstaculoPorDefecto", "obstaculoDef");
	elementoGrilla.addAttribute(atributoAlto);
	elementoGrilla.addAttribute(atributoAncho);
	elementoGrilla.addAttribute(atributoTipo);

	XmlElement elementoCaminoUno("camino", 3, 800);
	XmlAttribute atributoFilaC1("fila", "1");
	XmlAttribute atributoColumnaC1("columna", "5");
	elementoCaminoUno.addAttribute(atributoFilaC1);
	elementoCaminoUno.addAttribute(atributoColumnaC1);

	XmlElement bonusCaminoUno("bonus", 1, 20);
	XmlAttribute atributoBonus("tipo", "naranja");
	bonusCaminoUno.addAttribute(atributoBonus);

	elementoCaminoUno.addChild(bonusCaminoUno);

	elementoGrilla.addChild(elementoCaminoUno);

	List<TipoObstaculo> lo;

	std::string tipo = "uva";

	TipoBonus tb(tipo, '+');
	List<TipoBonus> lb;
	lb.add(tb);

	Grilla grilla(elementoGrilla, lo, lb);

	Celda c = grilla.getMatriz().at(1).at(5);
	
	Logger::getInstance()->closeLog();
	if(c.esOcupada())
	{
		return false;
	}

	return true;
}