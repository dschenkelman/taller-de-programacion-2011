#include "StdAfx.h"
#include "GrapherTests.h"
#include "Grapher.h"
#include <iostream>
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

GrapherTests::GrapherTests(void)
{
}

GrapherTests::~GrapherTests(void)
{
}

void GrapherTests::printLeaks(int leaks)
{
	std::cout << "Escenario Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

void GrapherTests::run(void)
{
	printResult("testGraficarEscenario", testGraficarEscenario());
	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

void GrapherTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

bool GrapherTests::testGraficarEscenario(void)
{
XmlElement elementoEscenario("escenario", 1, 1000);

	// se crea el xmlElement de grilla
	XmlElement elementoGrilla("grilla", 2, 999);
	XmlAttribute atributoAncho("ancho", "4");
	XmlAttribute atributoAlto("alto", "4");
	XmlAttribute atributoTipo("tipoobstaculopordefecto", "ladrillo");
	elementoGrilla.addAttribute(atributoAlto);
	elementoGrilla.addAttribute(atributoAncho);
	elementoGrilla.addAttribute(atributoTipo);

	// se crea el xmlElement de la lista de tipos bonus
	XmlElement elementoListaTiposBonus("tiposbonus", 200, 600);

	XmlElement elementoTipoBonus("tipoBonus", 201, 202);
	XmlAttribute atributoNombre("nombre", "uva");
	XmlAttribute atributoTextura("textura", "#");
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

	XmlElement elementoTipoObstaculoDos("tipoobstaculo", 605, 620);
	XmlAttribute atributoNombreDos("nombre", "ladrillo");
	XmlAttribute atributoTexturaDos("textura", "#");
	elementoTipoObstaculoDos.addAttribute(atributoNombreDos);
	elementoTipoObstaculoDos.addAttribute(atributoTexturaDos);

	elementoListaTiposObstaculo.addChild(elementoTipoObstaculoUno);
	elementoListaTiposObstaculo.addChild(elementoTipoObstaculoDos);

	// se crea un camino con bonus para la grilla
	XmlElement elementoCamino("camino", 2, 8);
	XmlAttribute atributoFila("fila", "2");
	XmlAttribute atributoColumna("columna", "2");
	elementoCamino.addAttribute(atributoFila);
	elementoCamino.addAttribute(atributoColumna);

	XmlElement elementoBonus("bonus", 4, 5);
	XmlAttribute atributoT("tipo", "uva");
	elementoBonus.addAttribute(atributoT);

	elementoCamino.addChild(elementoBonus);

	elementoGrilla.addChild(elementoCamino);

	// segundo camino
	XmlElement elementoCamino2("camino", 2, 8);
	XmlAttribute atributoFila2("fila", "1");
	XmlAttribute atributoColumna2("columna", "0");
	elementoCamino2.addAttribute(atributoFila2);
	elementoCamino2.addAttribute(atributoColumna2);
	elementoGrilla.addChild(elementoCamino2);

	// tercer camino
	XmlElement elementoCamino3("camino", 2, 8);
	XmlAttribute atributoFila3("fila", "1");
	XmlAttribute atributoColumna3("columna", "1");
	elementoCamino3.addAttribute(atributoFila3);
	elementoCamino3.addAttribute(atributoColumna3);
	elementoGrilla.addChild(elementoCamino3);

	// cuarto camino
	XmlElement elementoCamino4("camino", 2, 8);
	XmlAttribute atributoFila4("fila", "1");
	XmlAttribute atributoColumna4("columna", "2");
	elementoCamino4.addAttribute(atributoFila4);
	elementoCamino4.addAttribute(atributoColumna4);
	elementoGrilla.addChild(elementoCamino4);

	// quinto camino
	XmlElement elementoCamino5("camino", 2, 8);
	XmlAttribute atributoFila5("fila", "1");
	XmlAttribute atributoColumna5("columna", "3");
	elementoCamino5.addAttribute(atributoFila5);
	elementoCamino5.addAttribute(atributoColumna5);
	elementoGrilla.addChild(elementoCamino5);

	// sexto camino
	XmlElement elementoCamino6("camino", 2, 8);
	XmlAttribute atributoFila6("fila", "2");
	XmlAttribute atributoColumna6("columna", "2");
	elementoCamino6.addAttribute(atributoFila6);
	elementoCamino6.addAttribute(atributoColumna6);
	elementoGrilla.addChild(elementoCamino6);


	// se crean dos obstaculos para la grilla
	XmlElement elementoObstaculoUno("obstaculo", 4, 9);
	XmlAttribute atributoFilaO1("fila", "3");
	XmlAttribute atributoColumnaO1("columna", "0");
	XmlAttribute atributoTipoO1("tipo", "ladrillo");
	elementoObstaculoUno.addAttribute(atributoFilaO1);
	elementoObstaculoUno.addAttribute(atributoColumnaO1);
	elementoObstaculoUno.addAttribute(atributoTipoO1);

	XmlElement elementoObstaculoDos("obstaculo", 9, 18);
	XmlAttribute atributoFilaO2("fila", "3");
	XmlAttribute atributoColumnaO2("columna", "3");
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

	// Creo un graficador
	Grapher grapher;
	
	// Dibujo el escenario
	grapher.draw(escenario);

	//tareas de finalizacion del test
	Logger::getInstance()->closeLog();

	return true;
}