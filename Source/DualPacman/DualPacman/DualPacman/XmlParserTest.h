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
	bool testLineNumberEqualsOne(void);
	bool testLineNumberEqualsTwo(void);
	bool testTagNameNotNull(void);
	bool testTagAttributeListNotNULL(void);
	bool testFileNotExists(void);
	bool testMissingGTSymbol(void);
	bool testMissingLTSymbol(void);
	bool testNoChildrenTag(void);
	bool testMissingQuotes(void);
	bool testParseReturnsXmlRootElement(void);
	bool testElementWithUnknownNameIsIgnored(void);
	bool testElementThatIsNotClosedIsAutomaticallyClosed(void);
	bool testNotOpeninigOrClosingQuotesDoesNotAddAnyAttributesToElement(void);
	~XmlParserTest(void);
};
