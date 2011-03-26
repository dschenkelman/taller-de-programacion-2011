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
	~XmlParserTest(void);
};
