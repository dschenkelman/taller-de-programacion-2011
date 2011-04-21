#include "StdAfx.h"
#include "TexturaTests.h"
#include <string>
#include <iostream>
#include "Textura.h"
#include "Logger.h"
#include <limits>

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
	printResult("testBoundsAreZeroAndMaxIntWhenNotSpecified", testBoundsAreZeroAndMaxIntWhenNotSpecified());
	printResult("testBoundsAreCorrectWhenSpecified", testBoundsAreCorrectWhenSpecified());
	printResult("testBoundStringValuesAreNotConsidered", testBoundStringValuesAreNotConsidered());
	printResult("testBoundNegativeValuesAreNotConsidered", testBoundNegativeValuesAreNotConsidered());
	printResult("testRightOrBottomLowerThanLeftOrTopUseDefaults", testRightOrBottomLowerThanLeftOrTopUseDefaults());
	printResult("testDefaultAlfaIsFF00FF", testDefaultAlfaIsFF00FF());
	printResult("testGetsAlphaFromElementCorrectly", testGetsAlphaFromElementCorrectly());
	printResult("testAlphaWithoutSharpUsesDefaultDueToInvalidFormat", testAlphaWithoutSharpUsesDefaultDueToInvalidFormat());
	printResult("testAlphaWithInvalidHexCharacterUsesDefaultDueToInvalidFormat", testAlphaWithInvalidHexCharacterUsesDefaultDueToInvalidFormat());

	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

bool TexturaTests::testIsCreatedFromElementWithNameTextura(void)
{
	XmlElement elemento("Textura", 1, 100);
	XmlAttribute atributo1("nombre", "Frutilla");
	XmlAttribute atributo2("path", "Images/Frutilla");
	elemento.addAttribute(atributo1);
	elemento.addAttribute(atributo2);

	Textura textura(elemento);

	bool successCondition1 = textura.getNombre() == "Frutilla";
	bool successCondition2 = textura.getPath() == "Images/Frutilla";
	bool successCondition3 = !textura.hasError();

	return successCondition1 && successCondition2 && successCondition3;
}

bool TexturaTests::testHasErrorIfAttributeNameIsNotValid(void)
{
	XmlElement elemento("Textura", 1, 100);
	XmlAttribute atributo1("nombre", "Frutilla");
	XmlAttribute atributo2("path", "Images/Frutilla");
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
	XmlAttribute atributo1("path", "Images/Frutilla");
	elemento.addAttribute(atributo1);

	Textura textura(elemento);
	bool successCondition1 = textura.hasError();
	bool successCondition2 = textura.getPath() == "Images/Frutilla";

	Logger::closeLog();

	return successCondition1 && successCondition2;
}

bool TexturaTests::testBoundsAreZeroAndMaxIntWhenNotSpecified(void)
{
	XmlElement elemento("Textura", 1, 100);
	XmlAttribute atributo1("nombre", "Frutilla");
	XmlAttribute atributo2("path", "Images/Frutilla");
	elemento.addAttribute(atributo1);
	elemento.addAttribute(atributo2);

	Textura textura(elemento);

	bool successCondition1 = textura.getLeft() == 0;
	bool successCondition2 = textura.getTop() == 0;
	bool successCondition3 = textura.getRight() == numeric_limits<int>::max();
	bool successCondition4 = textura.getBottom() == numeric_limits<int>::max();
	bool successCondition5 = !textura.hasError();

	Logger::closeLog();

	return successCondition1 && successCondition2 &&  
		successCondition3 && successCondition4 && successCondition5;
}

bool TexturaTests::testBoundsAreCorrectWhenSpecified(void)
{
	XmlElement elemento("Textura", 1, 100);
	XmlAttribute atributo1("nombre", "Frutilla");
	XmlAttribute atributo2("path", "Images/Frutilla");
	XmlAttribute atributo3("top", "100");
	XmlAttribute atributo4("left", "200");
	XmlAttribute atributo5("right", "300");
	XmlAttribute atributo6("bottom", "400");
	elemento.addAttribute(atributo1);
	elemento.addAttribute(atributo2);
	elemento.addAttribute(atributo3);
	elemento.addAttribute(atributo4);
	elemento.addAttribute(atributo5);
	elemento.addAttribute(atributo6);

	Textura textura(elemento);

	bool successCondition1 = textura.getLeft() == 200;
	bool successCondition2 = textura.getTop() == 100;
	bool successCondition3 = textura.getRight() == 300;
	bool successCondition4 = textura.getBottom() == 400;
	bool successCondition5 = !textura.hasError();

	Logger::closeLog();	

	return successCondition1 && successCondition2 &&  
		successCondition3 && successCondition4 && successCondition5;
}

bool TexturaTests::testBoundStringValuesAreNotConsidered(void)
{
	XmlElement elemento("Textura", 1, 100);
	XmlAttribute atributo1("nombre", "Frutilla");
	XmlAttribute atributo2("path", "Images/Frutilla");
	XmlAttribute atributo3("top", "A");
	XmlAttribute atributo4("left", "B");
	XmlAttribute atributo5("right", "C");
	XmlAttribute atributo6("bottom", "D");
	elemento.addAttribute(atributo1);
	elemento.addAttribute(atributo2);
	elemento.addAttribute(atributo3);
	elemento.addAttribute(atributo4);
	elemento.addAttribute(atributo5);
	elemento.addAttribute(atributo6);

	Textura textura(elemento);
	
	bool successCondition1 = textura.getLeft() == 0;
	bool successCondition2 = textura.getTop() == 0;
	bool successCondition3 = textura.getRight() == numeric_limits<int>::max();
	bool successCondition4 = textura.getBottom() == numeric_limits<int>::max();
	bool successCondition5 = !textura.hasError();

	Logger::closeLog();

	return successCondition1 && successCondition2 &&  
		successCondition3 && successCondition4 && successCondition5;
}

bool TexturaTests::testBoundNegativeValuesAreNotConsidered(void)
{
	XmlElement elemento("Textura", 1, 100);
	XmlAttribute atributo1("nombre", "Frutilla");
	XmlAttribute atributo2("path", "Images/Frutilla");
	XmlAttribute atributo3("top", "-100");
	XmlAttribute atributo4("left", "-200");
	XmlAttribute atributo5("right", "-300");
	XmlAttribute atributo6("bottom", "-400");
	elemento.addAttribute(atributo1);
	elemento.addAttribute(atributo2);
	elemento.addAttribute(atributo3);
	elemento.addAttribute(atributo4);
	elemento.addAttribute(atributo5);
	elemento.addAttribute(atributo6);

	Textura textura(elemento);
	
	bool successCondition1 = textura.getLeft() == 0;
	bool successCondition2 = textura.getTop() == 0;
	bool successCondition3 = textura.getRight() == numeric_limits<int>::max();
	bool successCondition4 = textura.getBottom() == numeric_limits<int>::max();
	bool successCondition5 = !textura.hasError();

	Logger::closeLog();

	return successCondition1 && successCondition2 &&  
		successCondition3 && successCondition4 && successCondition5;
}

bool TexturaTests::testRightOrBottomLowerThanLeftOrTopUseDefaults(void)
{
	XmlElement elemento("Textura", 1, 100);
	XmlAttribute atributo1("nombre", "Frutilla");
	XmlAttribute atributo2("path", "Images/Frutilla");
	XmlAttribute atributo3("top", "100");
	XmlAttribute atributo4("left", "200");
	XmlAttribute atributo5("right", "150");
	XmlAttribute atributo6("bottom", "50");
	elemento.addAttribute(atributo1);
	elemento.addAttribute(atributo2);
	elemento.addAttribute(atributo3);
	elemento.addAttribute(atributo4);
	elemento.addAttribute(atributo5);
	elemento.addAttribute(atributo6);

	Textura textura(elemento);
	
	bool successCondition1 = textura.getLeft() == 200;
	bool successCondition2 = textura.getTop() == 100;
	bool successCondition3 = textura.getRight() == numeric_limits<int>::max();
	bool successCondition4 = textura.getBottom() == numeric_limits<int>::max();
	bool successCondition5 = !textura.hasError();

	Logger::closeLog();

	return successCondition1 && successCondition2 &&  
		successCondition3 && successCondition4 && successCondition5;
}

bool TexturaTests::testDefaultAlfaIsFF00FF(void)
{
	XmlElement elemento("Textura", 1, 100);
	XmlAttribute atributo1("nombre", "Frutilla");
	XmlAttribute atributo2("path", "Images/Frutilla");
	elemento.addAttribute(atributo1);
	elemento.addAttribute(atributo2);

	Textura textura(elemento);
	bool successCondition1 = textura.getRed() == 255;
	bool successCondition2 = textura.getGreen() == 0;
	bool successCondition3 = textura.getBlue() == 255;
	bool successCondition4 = !textura.hasError();

	Logger::closeLog();

	return successCondition1 && successCondition2 &&  
		successCondition3 && successCondition4;
}

bool TexturaTests::testGetsAlphaFromElementCorrectly()
{
	XmlElement elemento("Textura", 1, 100);
	XmlAttribute atributo1("nombre", "Frutilla");
	XmlAttribute atributo2("path", "Images/Frutilla");
	
	// r = 17, g = 34, b = 51
	XmlAttribute atributo3("alpha", "#112233");

	elemento.addAttribute(atributo1);
	elemento.addAttribute(atributo2);
	elemento.addAttribute(atributo3);

	Textura textura(elemento);
	bool successCondition1 = textura.getRed() == 17;
	bool successCondition2 = textura.getGreen() == 34;
	bool successCondition3 = textura.getBlue() == 51;
	bool successCondition4 = !textura.hasError();

	Logger::closeLog();

	return successCondition1 && successCondition2 &&  
		successCondition3 && successCondition4;
}

bool TexturaTests::testAlphaWithoutSharpUsesDefaultDueToInvalidFormat(void)
{
	XmlElement elemento("Textura", 1, 100);
	XmlAttribute atributo1("nombre", "Frutilla");
	XmlAttribute atributo2("path", "Images/Frutilla");
	
	// r = 17, g = 34, b = 51
	XmlAttribute atributo3("alpha", "112233");

	elemento.addAttribute(atributo1);
	elemento.addAttribute(atributo2);
	elemento.addAttribute(atributo3);

	Textura textura(elemento);
	bool successCondition1 = textura.getRed() == 255;
	bool successCondition2 = textura.getGreen() == 0;
	bool successCondition3 = textura.getBlue() == 255;
	bool successCondition4 = !textura.hasError();

	Logger::closeLog();

	return successCondition1 && successCondition2 &&  
		successCondition3 && successCondition4;
}

bool TexturaTests::testAlphaWithInvalidHexCharacterUsesDefaultDueToInvalidFormat(void)
{
	XmlElement elemento("Textura", 1, 100);
	XmlAttribute atributo1("nombre", "Frutilla");
	XmlAttribute atributo2("path", "Images/Frutilla");
	
	// G is not Hex
	XmlAttribute atributo3("alpha", "#11G233");

	elemento.addAttribute(atributo1);
	elemento.addAttribute(atributo2);
	elemento.addAttribute(atributo3);

	Textura textura(elemento);
	bool successCondition1 = textura.getRed() == 255;
	bool successCondition2 = textura.getGreen() == 0;
	bool successCondition3 = textura.getBlue() == 255;
	bool successCondition4 = !textura.hasError();

	Logger::closeLog();

	return successCondition1 && successCondition2 &&  
		successCondition3 && successCondition4;
}

TexturaTests::~TexturaTests(void)
{
}