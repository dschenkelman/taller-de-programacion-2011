#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#pragma once

class XmlParserTest
{
public:
	XmlParserTest(void);
	void run(void);
	void printResult(std::string testName, bool result);
	void printLeaks(int leaks);
	bool testLineNumberEqualsTwo(void);
	bool testLineNumberEqualsThree(void);
	bool testTagNameNotNull(void);
	bool testTagAttributeListNotNULL(void);
	bool testFileNotExists(void);
	bool testMissingGTSymbol(void);
	bool testMissingLTSymbol(void);
	bool testNoChildrenTag(void);
	bool testMissingQuotes(void);
	~XmlParserTest(void);
};
