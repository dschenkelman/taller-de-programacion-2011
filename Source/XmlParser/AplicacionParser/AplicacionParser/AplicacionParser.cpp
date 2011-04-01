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
#include "GrillaTests.h"
#include <iostream>
using namespace std;

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

	cout<<"Test de XmlParser"<<endl;
	XmlParserTest xmlParserTest;
	xmlParserTest.run();

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

	cout<<"Test de Grilla"<<endl;
	GrillaTests grillaTests;
	grillaTests.run();

	char aux;
	cin >> aux;

	return 0;
}

