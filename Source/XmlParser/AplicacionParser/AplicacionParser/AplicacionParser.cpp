// AplicacionParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ListTests.h"
#include "LoggerTests.h"
#include "XmlParser.h"
#include "StackTests.h"
#include "StringTests.h"
#include "XmlParserTest.h"
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

	cout<<"Test de String"<<endl;
	StringTests stringTests;
	stringTests.run();

	cout<<"Test de Logger"<<endl;
	LoggerTests loggerTests;
	loggerTests.run();

	cout<<"Test de XmlParser"<<endl;
	XmlParserTest xmlParserTest;
	xmlParserTest.run();


	char aux;
	cin >> aux;

	return 0;
}

