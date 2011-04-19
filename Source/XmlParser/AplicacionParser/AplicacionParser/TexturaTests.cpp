#include "StdAfx.h"
#include "TexturaTests.h"
#include <string>
#include <iostream>
#include "Textura.h"
#include "Logger.h"

//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

TexturaTests::TexturaTests(void)
{
}

void TexturaTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

void TexturaTests::printLeaks(int leaks)
{
	std::cout << "Textura Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

void TexturaTests::run()
{
	printResult("testIsCreatedFromElementWithNameTextura", testIsCreatedFromElementWithNameTextura());
	printResult("testHasErrorIfAttributeNameIsNotValid", testHasErrorIfAttributeNameIsNotValid());
	printResult("testHasErrorIfItDoesNotHaveArchivoAttribute", testHasErrorIfItDoesNotHaveArchivoAttribute());
	printResult("testHasErrorIfItDoesNotHaveNombreAttribute", testHasErrorIfItDoesNotHaveNombreAttribute());
	
	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

bool TexturaTests::testIsCreatedFromElementWithNameTextura(void)
{
	XmlElement elemento("Textura", 1, 100);
	XmlAttribute atributo1("nombre", "Frutilla");
	XmlAttribute atributo2("archivo", "Images/Frutilla");
	elemento.addAttribute(atributo1);
	elemento.addAttribute(atributo2);

	Textura textura(elemento);

	bool successCondition1 = textura.getNombre() == "Frutilla";
	bool successCondition2 = textura.getArchivo() == "Images/Frutilla";
	bool successCondition3 = !textura.hasError();

	return successCondition1 && successCondition2 && successCondition3;
}

bool TexturaTests::testHasErrorIfAttributeNameIsNotValid(void)
{
	XmlElement elemento("Textura", 1, 100);
	XmlAttribute atributo1("nombre", "Frutilla");
	XmlAttribute atributo2("archivo", "Images/Frutilla");
	XmlAttribute atributo3("incorrecto", "incorrecto");
	elemento.addAttribute(atributo1);
	elemento.addAttribute(atributo2);
	elemento.addAttribute(atributo3);

	Textura textura(elemento);
	bool successCondition = textura.hasError();

	Logger::closeLog();

	return successCondition;
}

bool TexturaTests::testHasErrorIfItDoesNotHaveArchivoAttribute(void)
{
	XmlElement elemento("Textura", 1, 100);
	XmlAttribute atributo1("nombre", "Frutilla");
	elemento.addAttribute(atributo1);

	Textura textura(elemento);
	bool successCondition1 = textura.hasError();
	bool successCondition2 = textura.getNombre() == "Frutilla";

	Logger::closeLog();

	return successCondition1 && successCondition2;
}

bool TexturaTests::testHasErrorIfItDoesNotHaveNombreAttribute(void)
{
	XmlElement elemento("Textura", 1, 100);
	XmlAttribute atributo1("archivo", "Images/Frutilla");
	elemento.addAttribute(atributo1);

	Textura textura(elemento);
	bool successCondition1 = textura.hasError();
	bool successCondition2 = textura.getArchivo() == "Images/Frutilla";

	Logger::closeLog();

	return successCondition1 && successCondition2;
}

TexturaTests::~TexturaTests(void)
{
}