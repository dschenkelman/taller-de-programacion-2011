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
	XmlAttribute atributoAncho("ancho", "10");
	XmlAttribute atributoAlto("alto", "10");
	XmlAttribute atributoTipo("tipoObstaculoPorDefecto", "ladrillo");
	elementoGrilla.addAttribute(atributoAlto);
	elementoGrilla.addAttribute(atributoAncho);
	elementoGrilla.addAttribute(atributoTipo);

	// se crea el xmlElement de la lista de tipos bonus
	XmlElement elementoListaTiposBonus("tiposBonus", 200, 600);

	XmlElement elementoTipoBonus("tipoBonus", 201, 202);
	XmlAttribute atributoNombre("nombre", "uva");
	XmlAttribute atributoTextura("textura", "+");
	elementoTipoBonus.addAttribute(atributoNombre);
	elementoTipoBonus.addAttribute(atributoTextura);

	elementoListaTiposBonus.addChild(elementoTipoBonus);

	// se crea el xmlElement de la lista de tipos obstaculos
	XmlElement elementoListaTiposObstaculo("tiposObstaculos", 600, 700);
	
	XmlElement elementoTipoObstaculoUno("tipoObstaculo", 600, 605);
	XmlAttribute atributoNombreUno("nombre", "yunque");
	XmlAttribute atributoTexturaUno("textura", "*");
	elementoTipoObstaculoUno.addAttribute(atributoNombreUno);
	elementoTipoObstaculoUno.addAttribute(atributoTexturaUno);

	XmlElement elementoTipoObstaculoDos("tipoObstaculos", 605, 620);
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
	XmlAttribute atributoFilaO2("fila", "9");
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

	// Creo un graficador
	Grapher* grapher = new Grapher();
	
	// Dibujo el escenario
	grapher->draw(escenario);

	delete grapher;

	return true;
}