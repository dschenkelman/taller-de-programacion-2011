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
	printResult("testColocarDosObjetosEnMismaPosicionGuardaElPrimero", testColocarDosObjetosEnMismaPosicionGuardaElPrimero());
	printResult("testNonValidAttributeMakesHasErrorTrue", testNonValidAttributeMakesHasErrorTrue());

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
	
	bool res = grilla.getAncho() == defGridAncho;
	return (res) ? true:false;
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
	
	bool res = grilla.getAlto() == defGridAlto;
	return (res) ? true:false;
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
	XmlAttribute atributoTipo("tipoobstaculopordefecto", "obstaculoDef");
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

	XmlElement bonusCaminoUno("bonus", 1, 20);
	XmlAttribute atributoBonus("tipo", "uva");
	bonusCaminoUno.addAttribute(atributoBonus);
	elementoCaminoUno.addChild(bonusCaminoUno);

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

	// se crea el tipo bonus y se agrega a la lista de tipos bonus
	std::string tipo = "uva";

	TipoBonus tb(tipo, '+');
	lb.add(tb);

	// se crea el tipo obstaculo por defecto y se agrega a la lista de tipos obstaculos
	std::string nombreTipoO = "obstaculoDef";

	TipoObstaculo tipoO(nombreTipoO, '´');
	lo.add(tipoO);

	Grilla grilla(elementoGrilla, lo, lb);

	int prueba = grilla.getCelda(2,9)->getFila();

	Logger::getInstance()->closeLog();

	if (grilla.getCelda(2, 9)->getFila() != 2 || grilla.getCelda(2, 9)->getColumna() != 9)
	{
		return false;
	}

	if (grilla.getCelda(1, 5)->getFila() != 1 || grilla.getCelda(1, 5)->getColumna() != 5)
	{
		return false;
	}

	if (grilla.getCelda(7, 4)->getFila() != 7 || grilla.getCelda(7, 4)->getColumna() != 4)
	{
		return false;
	}

	if (grilla.getCelda(4, 6)->getFila() != 4 || grilla.getCelda(4, 6)->getColumna() != 6)
	{
		return false;
	}

	Camino* cam = (Camino*) grilla.getCelda(1, 5);
	
	if (cam->getBonus().getTipoBonus().getNombre() != "uva")
	{
		return false;
	}

	if (cam->getBonus().getTipoBonus().getTextura() != '+')
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
	List<TipoBonus> lb;

	// se crea el tipo bonus y se agrega a la lista de tipos bonus
	std::string tipo = "uva";

	TipoBonus tb(tipo, '+');
	lb.add(tb);

	Grilla grilla(elementoGrilla, lo, lb);

	Celda* c = grilla.getCelda(1, 5);
	
	Logger::getInstance()->closeLog();
	if(c->esOcupada())
	{
		return false;
	}

	return true;
}

bool GrillaTests::testColocarDosObjetosEnMismaPosicionGuardaElPrimero(void)
{
	XmlElement elementoGrilla("Grilla", 1, 1000);
	XmlAttribute atributoAlto("alto", "10");
	XmlAttribute atributoAncho("ancho", "10");
	XmlAttribute atributoTipo("tipoobstaculopordefecto", "obstaculoDef");
	elementoGrilla.addAttribute(atributoAlto);
	elementoGrilla.addAttribute(atributoAncho);
	elementoGrilla.addAttribute(atributoTipo);

	XmlElement elementoCamino("camino", 3, 800);
	XmlAttribute atributoFilaC1("fila", "1");
	XmlAttribute atributoColumnaC1("columna", "5");
	elementoCamino.addAttribute(atributoFilaC1);
	elementoCamino.addAttribute(atributoColumnaC1);

	XmlElement elementoObstaculo("obstaculo", 3, 800);
	XmlAttribute atributoFilaO1("fila", "1");
	XmlAttribute atributoColumnaO1("columna", "5");
	elementoObstaculo.addAttribute(atributoFilaO1);
	elementoObstaculo.addAttribute(atributoColumnaO1);

	elementoGrilla.addChild(elementoObstaculo);
	elementoGrilla.addChild(elementoCamino);

	List<TipoBonus> tb;
	List<TipoObstaculo> to;

	// Se agrega el obstaculo por defecto a la lista obstaculos
	std::string nombreTipoO = "obstaculoDef";

	TipoObstaculo tipoO(nombreTipoO, '´');
	to.add(tipoO);

	// Se crea la grilla
	Grilla grilla(elementoGrilla, to, tb);

	Celda* c = grilla.getCelda(1, 5);
	Obstaculo* obs = (Obstaculo*) c;

	// se cierra el logger
	Logger::getInstance()->closeLog();

	if(obs->getTipo() != "obstaculoDef")
	{
		return false;
	}

	return true;
}

bool GrillaTests::testNonValidAttributeMakesHasErrorTrue(void)
{
	XmlElement elementoGrilla("Grilla", 1, 1000);
	XmlAttribute atributoAlto("alto", "10");
	XmlAttribute atributoAncho("ancho", "10");
	XmlAttribute atributoTipo("tipoobstaculopordefecto", "obstaculoDef");
	XmlAttribute atributoInvalido("invalido", "invalido");
	elementoGrilla.addAttribute(atributoAlto);
	elementoGrilla.addAttribute(atributoAncho);
	elementoGrilla.addAttribute(atributoTipo);
	elementoGrilla.addAttribute(atributoInvalido);

	XmlElement elementoCaminoUno("camino", 3, 800);
	XmlAttribute atributoFilaC1("fila", "1");
	XmlAttribute atributoColumnaC1("columna", "5");
	elementoCaminoUno.addAttribute(atributoFilaC1);
	elementoCaminoUno.addAttribute(atributoColumnaC1);

	elementoGrilla.addChild(elementoCaminoUno);

	List<TipoObstaculo> lo;
	List<TipoBonus> lb;

	Grilla grilla(elementoGrilla, lo, lb);
	
	Logger::closeLog();

	return grilla.hasError();
}