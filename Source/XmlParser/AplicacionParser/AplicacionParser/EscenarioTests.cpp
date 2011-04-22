#include "StdAfx.h"
#include "EscenarioTests.h"
#include "Celda.h"
#include "Camino.h"
#include "Obstaculo.h"
#include <exception>
#include <iostream>
#include <limits>
using namespace std;
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

EscenarioTests::EscenarioTests(void)
{
}

EscenarioTests::~EscenarioTests(void)
{
}

void EscenarioTests::printLeaks(int leaks)
{
	std::cout << "Escenario Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

void EscenarioTests::run(void)
{
	printResult("testCrearEscenarioCreaCorrectamente", testCrearEscenarioCreaCorrectamente());
	printResult("testNonValidAttributeMakesHasErrorTrue", testNonValidAttributeMakesHasErrorTrue());
	printResult("testCorrectlyPopulatesTexturas", testCorrectlyPopulatesTexturas());

	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

void EscenarioTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

bool EscenarioTests::testCrearEscenarioCreaCorrectamente(void)
{
	XmlElement elementoEscenario("escenario", 1, 1000);

	// se crea el xmlElement de grilla
	XmlElement elementoGrilla("grilla", 2, 999);
	XmlAttribute atributoAncho("ancho", "10");
	XmlAttribute atributoAlto("alto", "10");
	XmlAttribute atributoTipo("tipoobstaculopordefecto", "ladrillo");
	elementoGrilla.addAttribute(atributoAlto);
	elementoGrilla.addAttribute(atributoAncho);
	elementoGrilla.addAttribute(atributoTipo);

	// se crea el xmlElement de la lista de tipos bonus
	XmlElement elementoListaTiposBonus("tiposbonus", 200, 600);

	XmlElement elementoTipoBonus("tipobonus", 201, 202);
	XmlAttribute atributoNombre("nombre", "uva");
	XmlAttribute atributoTextura("textura", "+");
	elementoTipoBonus.addAttribute(atributoNombre);
	elementoTipoBonus.addAttribute(atributoTextura);

	elementoListaTiposBonus.addChild(elementoTipoBonus);

	// se crea el xmlElement de la lista de tipos obstaculos
	XmlElement elementoListaTiposObstaculo("tiposobstaculos", 600, 700);
	
	XmlElement elementoTipoObstaculoUno("tipoobstaculo", 600, 605);
	XmlAttribute atributoNombreUno("nombre", "yunque");
	XmlAttribute atributoTexturaUno("textura", "*");
	elementoTipoObstaculoUno.addAttribute(atributoNombreUno);
	elementoTipoObstaculoUno.addAttribute(atributoTexturaUno);

	XmlElement elementoTipoObstaculoDos("tipoobstaculos", 605, 620);
	XmlAttribute atributoNombreDos("nombre", "ladrillo");
	XmlAttribute atributoTexturaDos("textura", "-");
	elementoTipoObstaculoDos.addAttribute(atributoNombreDos);
	elementoTipoObstaculoDos.addAttribute(atributoTexturaDos);

	elementoListaTiposObstaculo.addChild(elementoTipoObstaculoUno);
	elementoListaTiposObstaculo.addChild(elementoTipoObstaculoDos);

	// se crea un camino con bonus para la grilla
	XmlElement elementoCamino("camino", 2, 8);
	XmlAttribute atributoFila("fila", "4");
	XmlAttribute atributoColumna("columna", "9");
	elementoCamino.addAttribute(atributoFila);
	elementoCamino.addAttribute(atributoColumna);

	XmlElement elementoBonus("bonus", 4, 5);
	XmlAttribute atributoT("tipo", "uva");
	elementoBonus.addAttribute(atributoT);

	elementoCamino.addChild(elementoBonus);

	elementoGrilla.addChild(elementoCamino);

	// se crean dos obstaculos para la grilla

	XmlElement elementoObstaculoUno("obstaculo", 4, 9);
	XmlAttribute atributoFilaO1("fila", "8");
	XmlAttribute atributoColumnaO1("columna", "4");
	elementoObstaculoUno.addAttribute(atributoFilaO1);
	elementoObstaculoUno.addAttribute(atributoColumnaO1);

	XmlElement elementoObstaculoDos("obstaculo", 9, 18);
	XmlAttribute atributoFilaO2("fila", "2");
	XmlAttribute atributoColumnaO2("columna", "7");
	XmlAttribute atributoTipoO2("tipo", "yunque");
	elementoObstaculoDos.addAttribute(atributoFilaO2);
	elementoObstaculoDos.addAttribute(atributoColumnaO2);
	elementoObstaculoDos.addAttribute(atributoTipoO2);

	elementoGrilla.addChild(elementoObstaculoUno);
	elementoGrilla.addChild(elementoObstaculoDos);

	// se agregan la grilla y las listas al xml de escenario

	elementoEscenario.addChild(elementoGrilla);
	elementoEscenario.addChild(elementoListaTiposBonus);
	elementoEscenario.addChild(elementoListaTiposObstaculo);

	// se crea el escenario
	Escenario escenario(elementoEscenario);

	Logger::closeLog();

	if (! escenario.getGrilla().getCelda(4, 9)->esOcupada())
	{
		return false;
	}

	if (! escenario.getGrilla().getCelda(8, 4)->esOcupada())
	{
		return false;
	}

	if (! escenario.getGrilla().getCelda(2, 7)->esOcupada())
	{
		return false;
	}

	Grilla& grilla = escenario.getGrilla();
	Celda* celUno = grilla.getCelda(4,9);
	Camino* cam = (Camino*) celUno;

	if (cam->getBonus().getTipo() != "uva")
	{
		return false;
	}

	Celda* celDos = escenario.getGrilla().getCelda(8, 4);
	Obstaculo* obsUno = (Obstaculo*) celDos;

	if (obsUno->getTipo() != "ladrillo")
	{
		return false;
	}

	Celda* celTres = escenario.getGrilla().getCelda(2, 7);
	Obstaculo* obsDos = (Obstaculo*) celTres;

	if (obsDos->getTipo() != "yunque")
	{
		return false;
	}

	return true;
}

bool EscenarioTests::testNonValidAttributeMakesHasErrorTrue()
{
	XmlElement elementoEscenario("escenario", 1, 1000);
	XmlAttribute atributoNombreE("nombre", "escenario test");
	XmlAttribute atributoInvalido("invalido", "invalido");
	elementoEscenario.addAttribute(atributoNombreE);
	elementoEscenario.addAttribute(atributoInvalido);

	// se crea el xmlElement de grilla
	XmlElement elementoGrilla("grilla", 2, 999);
	XmlAttribute atributoAncho("ancho", "10");
	XmlAttribute atributoAlto("alto", "10");
	XmlAttribute atributoTipo("tipoobstaculopordefecto", "ladrillo");
	elementoGrilla.addAttribute(atributoAlto);
	elementoGrilla.addAttribute(atributoAncho);
	elementoGrilla.addAttribute(atributoTipo);

	// se crea el xmlElement de la lista de tipos bonus
	XmlElement elementoListaTiposBonus("tiposbonus", 200, 600);

	XmlElement elementoTipoBonus("tipobonus", 201, 202);
	XmlAttribute atributoNombre("nombre", "uva");
	XmlAttribute atributoTextura("textura", "+");
	elementoTipoBonus.addAttribute(atributoNombre);
	elementoTipoBonus.addAttribute(atributoTextura);

	elementoListaTiposBonus.addChild(elementoTipoBonus);

	// se crea el xmlElement de la lista de tipos obstaculos
	XmlElement elementoListaTiposObstaculo("tiposobstaculos", 600, 700);
	
	XmlElement elementoTipoObstaculoUno("tipoobstaculo", 600, 605);
	XmlAttribute atributoNombreUno("nombre", "yunque");
	XmlAttribute atributoTexturaUno("textura", "*");
	elementoTipoObstaculoUno.addAttribute(atributoNombreUno);
	elementoTipoObstaculoUno.addAttribute(atributoTexturaUno);

	XmlElement elementoTipoObstaculoDos("tipoobstaculos", 605, 620);
	XmlAttribute atributoNombreDos("nombre", "ladrillo");
	XmlAttribute atributoTexturaDos("textura", "-");
	elementoTipoObstaculoDos.addAttribute(atributoNombreDos);
	elementoTipoObstaculoDos.addAttribute(atributoTexturaDos);

	elementoListaTiposObstaculo.addChild(elementoTipoObstaculoUno);
	elementoListaTiposObstaculo.addChild(elementoTipoObstaculoDos);

	// se crea un camino con bonus para la grilla
	XmlElement elementoCamino("camino", 2, 8);
	XmlAttribute atributoFila("fila", "4");
	XmlAttribute atributoColumna("columna", "9");
	elementoCamino.addAttribute(atributoFila);
	elementoCamino.addAttribute(atributoColumna);

	XmlElement elementoBonus("bonus", 4, 5);
	XmlAttribute atributoT("tipo", "uva");
	elementoBonus.addAttribute(atributoT);

	elementoCamino.addChild(elementoBonus);

	elementoGrilla.addChild(elementoCamino);

	// se crean dos obstaculos para la grilla

	XmlElement elementoObstaculoUno("obstaculo", 4, 9);
	XmlAttribute atributoFilaO1("fila", "8");
	XmlAttribute atributoColumnaO1("columna", "4");
	elementoObstaculoUno.addAttribute(atributoFilaO1);
	elementoObstaculoUno.addAttribute(atributoColumnaO1);

	XmlElement elementoObstaculoDos("obstaculo", 9, 18);
	XmlAttribute atributoFilaO2("fila", "2");
	XmlAttribute atributoColumnaO2("columna", "7");
	XmlAttribute atributoTipoO2("tipo", "yunque");
	elementoObstaculoDos.addAttribute(atributoFilaO2);
	elementoObstaculoDos.addAttribute(atributoColumnaO2);
	elementoObstaculoDos.addAttribute(atributoTipoO2);

	elementoGrilla.addChild(elementoObstaculoUno);
	elementoGrilla.addChild(elementoObstaculoDos);

	// se agregan la grilla y las listas al xml de escenario

	elementoEscenario.addChild(elementoGrilla);
	elementoEscenario.addChild(elementoListaTiposBonus);
	elementoEscenario.addChild(elementoListaTiposObstaculo);

	// se crea el escenario
	Escenario escenario(elementoEscenario);

	Logger::closeLog();

	return escenario.hasError();
}


bool EscenarioTests::testCorrectlyPopulatesTexturas()
{
	XmlElement elementoEscenario("escenario", 1, 1000);
	XmlElement elementoTexturas("texturas", 19, 22);
	XmlElement elementoTextura1("textura", 20, 20);
	XmlAttribute atributo1("nombre", "Frutilla");
	XmlAttribute atributo2("path", "Images/Frutilla");
	XmlAttribute atributo3("top", "100");
	XmlAttribute atributo4("left", "200");
	XmlAttribute atributo5("right", "300");
	XmlAttribute atributo6("bottom", "400");
	XmlAttribute atributo7("alpha", "#112233");
	XmlAttribute atributo8("delta", "10");
	XmlAttribute atributo9("rot", "20");
	
	XmlElement elementoTextura2("textura", 21, 21);
	XmlAttribute atributo10("nombre", "Pera");
	XmlAttribute atributo11("path", "Images/Pera");

	elementoTextura1.addAttribute(atributo1);
	elementoTextura1.addAttribute(atributo2);
	elementoTextura1.addAttribute(atributo3);
	elementoTextura1.addAttribute(atributo4);
	elementoTextura1.addAttribute(atributo5);
	elementoTextura1.addAttribute(atributo6);
	elementoTextura1.addAttribute(atributo7);
	elementoTextura1.addAttribute(atributo8);
	elementoTextura1.addAttribute(atributo9);

	elementoTextura2.addAttribute(atributo10);
	elementoTextura2.addAttribute(atributo11);

	elementoTexturas.addChild(elementoTextura1);
	elementoTexturas.addChild(elementoTextura2);
	elementoEscenario.addChild(elementoTexturas);

	Escenario escenario(elementoEscenario);

	List<Textura> texturas = escenario.getTexturas();
	
	bool successCondition = texturas.length() == 2;
	
	Textura t1 = texturas.at(0);
	Textura t2 = texturas.at(1);

	successCondition = successCondition && t1.getTop() == 100;
	successCondition = successCondition && t1.getLeft() == 200;
	successCondition = successCondition && t1.getRight() == 300;
	successCondition = successCondition && t1.getBottom() == 400;
	successCondition = successCondition && t1.getDelta() == 10;
	successCondition = successCondition && t1.getRotation() == 20;
	successCondition = successCondition && t1.getRed() == 17;
	successCondition = successCondition && t1.getGreen() == 34;
	successCondition = successCondition && t1.getBlue() == 51;

	successCondition = successCondition && t2.getTop() == 0;
	successCondition = successCondition && t2.getLeft() == 0;
	successCondition = successCondition && t2.getRight() == numeric_limits<int>::max();;
	successCondition = successCondition && t2.getBottom() == numeric_limits<int>::max();;
	successCondition = successCondition && t2.getDelta() == 0;
	successCondition = successCondition && t2.getRotation() == 0;
	successCondition = successCondition && t2.getRed() == 255;
	successCondition = successCondition && t2.getGreen() == 0;
	successCondition = successCondition && t2.getBlue() == 255;

	Logger::closeLog();

	return successCondition;
}