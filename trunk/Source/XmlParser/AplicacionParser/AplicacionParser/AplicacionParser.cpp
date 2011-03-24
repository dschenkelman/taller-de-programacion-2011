// AplicacionParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ListTests.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout<<"Test de lista"<<endl;
	ListTests tests;
	tests.run();
	char aux;
	cin >> aux;
	return 0;
}

