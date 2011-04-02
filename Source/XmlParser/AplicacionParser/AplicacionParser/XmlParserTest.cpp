#include "StdAfx.h"
#include "XmlParserTest.h"
#include "XmlParser.h"
#include <iostream>
#include <exception>
#include <string>
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
	std::cout << testName << (result ? ": Passed\n" : ": Failed!!!\n");
}

void XmlParserTest::printLeaks(int leaks)
{
	std::cout << "XmlParserTest: Hubo " << leaks << " memory leaks." << endl << endl;
}

void XmlParserTest::run(void) {
	
	printResult("testLineNumberEqualsTwo",testLineNumberEqualsTwo());
	printResult("testLineNumberEqualsThree",testLineNumberEqualsThree());
	printResult("testTagNameNotNull",testTagNameNotNull());
	printResult("testTagAttributeListNotNULL",testTagAttributeListNotNULL());
	printResult("testFileNotExists",testFileNotExists());
	printResult("testMissingGTSymbol",testMissingGTSymbol());
	printResult("testMissingLTSymbol",testMissingLTSymbol());
	printResult("testNoChildrenTag",testNoChildrenTag());
	printResult("testMissingQuotes",testMissingQuotes());

	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

bool XmlParserTest::testLineNumberEqualsTwo(void){

	XmlParser xmlParser;
	xmlParser.openFile("escenario.xml");
	xmlParser.getXmlLine();

	return (xmlParser.getLineNumber() == 2);
}

bool XmlParserTest::testLineNumberEqualsThree(void){

	XmlParser xmlParser;
	xmlParser.openFile("escenario.xml");
	xmlParser.getXmlLine();
	xmlParser.getXmlLine();

	return (xmlParser.getLineNumber() == 3);
}

bool XmlParserTest::testTagNameNotNull(void){

	XmlParser xmlParser;
	xmlParser.openFile("escenario.xml");
	xmlParser.getXmlLine();

	return (xmlParser.getLineTagName().length() > 0);
}

bool XmlParserTest::testTagAttributeListNotNULL(void){

	XmlParser xmlParser;
	xmlParser.openFile("escenario.xml");
	xmlParser.getXmlLine();
	return (xmlParser.getLineTagAttributes().capacity() > 0);
}

bool XmlParserTest::testFileNotExists(void){

	XmlParser xmlParser;
	xmlParser.openFile("sarasa.xml");
	
	return (!xmlParser.isFileOpen());
}

bool XmlParserTest::testMissingGTSymbol(void){

	XmlParser xmlParser;
	xmlParser.openFile("testLogger.xml");
	xmlParser.getXmlLine();
	
	return (xmlParser.lineHasErrors() == true);
}

bool XmlParserTest::testMissingLTSymbol(void){

	XmlParser xmlParser;
	xmlParser.openFile("testLogger2.xml");
	xmlParser.getXmlLine();
	
	return (xmlParser.lineHasErrors() == true);
}

bool XmlParserTest::testNoChildrenTag(void){
	XmlParser xmlParser;
	xmlParser.openFile("escenario.xml");
	xmlParser.getXmlLine();
	xmlParser.getXmlLine();
	xmlParser.getXmlLine(); //La tercera linea de escenario tiene un tag sin hijos
	return (xmlParser.tagHasNoChildren() == true);
}

bool XmlParserTest::testMissingQuotes(void){
	XmlParser xmlParser;
	xmlParser.openFile("escenario.xml");
	xmlParser.getXmlLine();
	xmlParser.getXmlLine();
	xmlParser.getXmlLine(); 
	xmlParser.getXmlLine();
	return (xmlParser.lineHasErrors() == true);
}