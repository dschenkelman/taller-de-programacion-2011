#include "StdAfx.h"
#include "XmlParserTest.h"
#include "XmlParser.h"
#include <iostream>
#include <exception>
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;
XmlParserTest::XmlParserTest(void)
{
}

XmlParserTest::~XmlParserTest(void)
{
}

void XmlParserTest::printResult(std::string testName, bool result)
{
	//std::cout << testName<< "has "<<(result ? ": Passed\n" : ": Failed!!!\n");
}

void XmlParserTest::printLeaks(int leaks)
{
	std::cout << "List Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

void XmlParserTest::run(void) {
	XmlParser xmlParser;
	xmlParser.openFile("escenario.xml");
	xmlParser.getXmlLine();

	cout<<"La linea numero: "<<xmlParser.getLineNumber()<<" leida es: "<<xmlParser.getLineRead()<<std::endl;
	xmlParser.parseLine();
	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}