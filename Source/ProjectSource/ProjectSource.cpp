// ProjectSource.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stack>
#include "xmlValidatorFixture.h"
#include "xmlTagUtilsTest.h"
#include <iostream>
using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	xmlValidatorFixture* fixture = new xmlValidatorFixture();
	fixture->run();
	delete fixture;
	cout<<"Test de parseo de atributos"<<endl;
	xmlTagUtilsTest miTest;
	miTest.run();
	char aux;
	cin >> aux;

	return 0;
}

