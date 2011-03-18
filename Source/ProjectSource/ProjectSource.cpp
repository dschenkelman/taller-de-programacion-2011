// ProjectSource.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stack>
#include "xmlValidatorFixture.h"
#include <iostream>
using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	xmlValidatorFixture* fixture = new xmlValidatorFixture();
	fixture->run();
	delete fixture;
	char aux;
	cin >> aux;
	return 0;
}

