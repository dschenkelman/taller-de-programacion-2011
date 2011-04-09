// AplicacionParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ListTests.h"
#include "LoggerTests.h"
#include "XmlParser.h"
#include "StackTests.h"
#include "StringTests.h"
#include "XmlParserTest.h"
#include "XmlElementTests.h"
#include "TipoObstaculoTests.h"
#include "TipoBonusTests.h"
#include "ObstaculoTests.h"
#include "CaminoTests.h"
#include "CellMatrixTests.h"
#include "GrillaTests.h"
#include "EscenarioTests.h"
#include "GrapherTests.h"
#include <iostream>
using namespace std;

//
//int main(int argc, char* argv[])
//{
//	if (argc != 2)
//	{
//		cout<<"Debe proveer el nombre del archivo a leer como argumento"<<endl;
//	}
//	
//	string fileName = argv[1];
//
//	XmlParser parser;
//	parser.openFile(fileName);
//	XmlElement root = parser.parse();
//	Escenario escenario(root);
//	Grapher grapher;
//	grapher.draw(escenario);
//
//	char aux;
//	cin >> aux;
//
//	return 0;
//}

int _tmain(int argc, _TCHAR* argv[])
{
	cout<<"Test de List<T>"<<endl;
	ListTests listTests;
	listTests.run();
	
	cout<<"Test de Stack<T>"<<endl;
	StackTests stackTests;
	stackTests.run();

	//cout<<"Test de String"<<endl;
	//StringTests stringTests;
	//stringTests.run();

	cout<<"Test de Logger"<<endl;
	LoggerTests loggerTests;
	loggerTests.run();

	cout<<"Test de XmlElement"<<endl;
	XmlElementTests xmlElementTests;
	xmlElementTests.run();

	cout<<"Test de TipoObstaculo"<<endl;
	TipoObstaculoTests tipoObstaculoTests;
	tipoObstaculoTests.run();

	cout<<"Test de TipoBonus"<<endl;
	TipoBonusTests tipoBonusTests;
	tipoBonusTests.run();

	cout<<"Test de Obstaculo"<<endl;
	ObstaculoTests obstaculoTests;
	obstaculoTests.run();

	cout<<"Test de Camino"<<endl;
	CaminoTests caminoTests;
	caminoTests.run();

	cout<<"Test de CellMatrix"<<endl;
	CellMatrixTests cellMatrixTests;
	cellMatrixTests.run();

	cout<<"Test de Grilla"<<endl;
	GrillaTests grillaTests;
	grillaTests.run();

	cout<<"Test de Escenario"<<endl;
	EscenarioTests escenarioTests;
	escenarioTests.run();

	cout<<"Test de XmlParser"<<endl;
	XmlParserTest xmlParserTest;
	xmlParserTest.run();

	cout<<"Test de Grapher"<<endl;
	GrapherTests grapherTest;
	grapherTest.run();

	/*char aux;
	cin >> aux;*/
	
	printf( "Press ENTER to continue... " );
	char c = getchar();

	return 0;
}

