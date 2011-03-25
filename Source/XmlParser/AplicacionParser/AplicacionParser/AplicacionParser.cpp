// AplicacionParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ListTests.h"
#include "XmlParser.h"
#include "StackTests.h"
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

	//XmlParser xmlParser;
	//xmlParser.openFile("testFile.xml");
	//xmlParser.getXmlLine();
	//cout<<"La línea leida es: "<<xmlParser.getLineRead();

	char aux;
	cin >> aux;

	return 0;
}

