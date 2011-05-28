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
	
	printResult("testLineNumberEqualsOne",testLineNumberEqualsOne());
	printResult("testLineNumberEqualsTwo",testLineNumberEqualsTwo());
	printResult("testTagNameNotNull",testTagNameNotNull());
	printResult("testTagAttributeListNotNULL",testTagAttributeListNotNULL());
	printResult("testFileNotExists",testFileNotExists());
	printResult("testMissingGTSymbol",testMissingGTSymbol());
	printResult("testMissingLTSymbol",testMissingLTSymbol());
	printResult("testNoChildrenTag",testNoChildrenTag());
	printResult("testMissingQuotes",testMissingQuotes());
	printResult("testParseReturnsXmlRootElement", testParseReturnsXmlRootElement());
	printResult("testElementWithUnknownNameIsIgnored", testElementWithUnknownNameIsIgnored());
	printResult("testElementThatIsNotClosedIsAutomaticallyClosed", testElementThatIsNotClosedIsAutomaticallyClosed());
	printResult("testNotOpeninigOrClosingQuotesDoesNotAddAnyAttributesToElement", testNotOpeninigOrClosingQuotesDoesNotAddAnyAttributesToElement());

	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

bool XmlParserTest::testLineNumberEqualsOne(void){

	XmlParser xmlParser;
	xmlParser.openFile("Files/escenario.xml");
	xmlParser.getXmlLine();

	return (xmlParser.getLineNumber() == 1);
}

bool XmlParserTest::testLineNumberEqualsTwo(void){

	XmlParser xmlParser;
	xmlParser.openFile("Files/escenario.xml");
	xmlParser.getXmlLine();
	xmlParser.getXmlLine();

	return (xmlParser.getLineNumber() == 2);
}

bool XmlParserTest::testTagNameNotNull(void){

	XmlParser xmlParser;
	xmlParser.openFile("Files/escenario.xml");
	xmlParser.getXmlLine();

	return (xmlParser.getLineTagName().length() > 0);
}

bool XmlParserTest::testTagAttributeListNotNULL(void){

	XmlParser xmlParser;
	xmlParser.openFile("Files/escenario.xml");
	xmlParser.getXmlLine();
	return (xmlParser.getLineTagAttributes().capacity() > 0);
}

bool XmlParserTest::testFileNotExists(void){

	XmlParser xmlParser;
	xmlParser.openFile("Files/sarasa.xml");
	
	return (!xmlParser.isFileOpen());
}

bool XmlParserTest::testMissingGTSymbol(void){

	XmlParser xmlParser;
	xmlParser.openFile("Files/testLogger.xml");
	xmlParser.getXmlLine();
	
	return (xmlParser.lineHasErrors() == true);
}

bool XmlParserTest::testMissingLTSymbol(void){

	XmlParser xmlParser;
	xmlParser.openFile("Files/testLogger2.xml");
	xmlParser.getXmlLine();
	
	return (xmlParser.lineHasErrors() == true);
}

bool XmlParserTest::testNoChildrenTag(void){
	XmlParser xmlParser;
	xmlParser.openFile("Files/escenario.xml");
	xmlParser.getXmlLine();
	xmlParser.getXmlLine();
	xmlParser.getXmlLine(); //La tercera linea de escenario tiene un tag sin hijos
	return (xmlParser.tagHasNoChildren() == true);
}

bool XmlParserTest::testMissingQuotes(void){
	XmlParser xmlParser;
	xmlParser.openFile("Files/escenarioMissingQuotes.xml");
	xmlParser.getXmlLine();
	xmlParser.getXmlLine();
	xmlParser.getXmlLine(); 
	xmlParser.getXmlLine();
	return (xmlParser.lineHasErrors() == true);
}

bool XmlParserTest::testParseReturnsXmlRootElement(void)
{
	XmlParser xmlParser;
	xmlParser.openFile("Files/escenario.xml");
	XmlElement root = xmlParser.parse();

	//testing root
	bool successCondition = root.getName() == "escenario";
	successCondition = successCondition && root.getValue("nombre") == "Escenario numero 1";
	successCondition = successCondition && root.getAttributes().length() == 1;
	successCondition = successCondition && root.getChildren().length() == 3;

	//testing grilla
	XmlElement grilla = root.getChildren().at(0);
	successCondition = successCondition && grilla.getValue("ancho") == "10";
	successCondition = successCondition && grilla.getValue("alto") == "15";
	successCondition = successCondition && grilla.getValue("tipoobstaculopordefecto") == "OBS1";
	successCondition = successCondition && grilla.getAttributes().length() == 3;
	successCondition = successCondition && grilla.getChildren().length() == 2;

	//testing obstaculo
	XmlElement obstaculo = grilla.getChildren().at(0);
	successCondition = successCondition && obstaculo.getValue("fila") == "1";
	successCondition = successCondition && obstaculo.getValue("columna") == "5";
	successCondition = successCondition && obstaculo.getValue("tipo") == "OBS1";
	successCondition = successCondition && obstaculo.getAttributes().length() == 3;

	XmlElement camino = grilla.getChildren().at(1);
	successCondition = successCondition && camino.getValue("fila") == "5";
	successCondition = successCondition && camino.getValue("columna") == "3";
	successCondition = successCondition && camino.getAttributes().length() == 2;
	successCondition = successCondition && camino.getChildren().length() == 1;

	XmlElement bonus = camino.getChildren().at(0);
	successCondition = successCondition && bonus.getValue("tipo") == "Frutillita";

	XmlElement tiposObstaculo = root.getChildren().at(1);
	successCondition = successCondition && tiposObstaculo.getChildren().length() == 1;

	XmlElement tipoObstaculo = tiposObstaculo.getChildren().at(0);
	successCondition = successCondition && tipoObstaculo.getValue("nombre") == "OBS1";
	successCondition = successCondition && tipoObstaculo.getValue("textura") == "*";

	return successCondition;
}

bool XmlParserTest::testElementWithUnknownNameIsIgnored(void)
{
	XmlParser xmlParser;
	xmlParser.openFile("Files/escenarioInvalidElement.xml");
	XmlElement root = xmlParser.parse();

	bool successCondition = !root.hasChildren();

	return successCondition;
}


bool XmlParserTest::testElementThatIsNotClosedIsAutomaticallyClosed(void)
{
	XmlParser xmlParser;
	xmlParser.openFile("Files/escenarioMissingClosingElements.xml");
	XmlElement root = xmlParser.parse();

	//testing root
	bool successCondition = root.getName() == "escenario";
	successCondition = successCondition && root.getValue("nombre") == "Escenario numero 1";
	successCondition = successCondition && root.getAttributes().length() == 1;
	successCondition = successCondition && root.getChildren().length() == 2;

	//testing grilla
	XmlElement grilla = root.getChildren().at(0);
	successCondition = successCondition && grilla.getValue("ancho") == "10";
	successCondition = successCondition && grilla.getValue("alto") == "15";
	successCondition = successCondition && grilla.getValue("tipoobstaculopordefault") == "OBS1";
	successCondition = successCondition && grilla.getAttributes().length() == 3;
	successCondition = successCondition && grilla.getChildren().length() == 2;

	//testing obstaculo
	XmlElement obstaculo = grilla.getChildren().at(0);
	successCondition = successCondition && obstaculo.getValue("fila") == "1";
	successCondition = successCondition && obstaculo.getValue("columna") == "5";
	successCondition = successCondition && obstaculo.getValue("tipo") == "OBS1";
	successCondition = successCondition && obstaculo.getAttributes().length() == 3;

	XmlElement camino = grilla.getChildren().at(1);
	successCondition = successCondition && camino.getValue("fila") == "5";
	successCondition = successCondition && camino.getValue("columna") == "3";
	successCondition = successCondition && camino.getAttributes().length() == 2;
	successCondition = successCondition && camino.getChildren().length() == 1;

	XmlElement bonus = camino.getChildren().at(0);
	successCondition = successCondition && bonus.getValue("tipo") == "Frutillita";

	XmlElement tiposObstaculo = root.getChildren().at(1);
	successCondition = successCondition && tiposObstaculo.getChildren().length() == 1;

	XmlElement tipoObstaculo = tiposObstaculo.getChildren().at(0);
	successCondition = successCondition && tipoObstaculo.getValue("nombreobstaculo") == "OBS1";
	successCondition = successCondition && tipoObstaculo.getValue("textura") == "*";

	return successCondition;	
}

bool XmlParserTest::testNotOpeninigOrClosingQuotesDoesNotAddAnyAttributesToElement(void)
{
	XmlParser xmlParser;
	xmlParser.openFile("Files/escenarioMissingQuotes2.xml");
	XmlElement root = xmlParser.parse();

	//testing root
	bool successCondition = root.getName() == "escenario";
	successCondition = successCondition && root.getValue("nombre") == "Escenario numero 1";
	successCondition = successCondition && root.getAttributes().length() == 1;
	successCondition = successCondition && root.getChildren().length() == 2;

	//testing grilla
	XmlElement grilla = root.getChildren().at(0);
	successCondition = successCondition && grilla.getAttributes().length() == 0;
	successCondition = successCondition && grilla.getChildren().length() == 2;

	//testing obstaculo
	XmlElement obstaculo = grilla.getChildren().at(0);
	successCondition = successCondition && obstaculo.getAttributes().length() == 0;

	XmlElement camino = grilla.getChildren().at(1);
	successCondition = successCondition && camino.getValue("fila") == "5";
	successCondition = successCondition && camino.getValue("columna") == "3";
	successCondition = successCondition && camino.getAttributes().length() == 2;
	successCondition = successCondition && camino.getChildren().length() == 1;

	XmlElement bonus = camino.getChildren().at(0);
	successCondition = successCondition && bonus.getValue("tipo") == "Frutillita";

	XmlElement tiposObstaculo = root.getChildren().at(1);
	successCondition = successCondition && tiposObstaculo.getChildren().length() == 1;

	XmlElement tipoObstaculo = tiposObstaculo.getChildren().at(0);
	successCondition = successCondition && tipoObstaculo.getValue("nombreobstaculo") == "OBS1";
	successCondition = successCondition && tipoObstaculo.getValue("textura") == "*";

	return successCondition;	
}

