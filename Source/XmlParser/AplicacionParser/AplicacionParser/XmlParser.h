#include <iostream>
#include <fstream>
#include <string>
#pragma once

class XmlParser
{
private:
	long lineNumber;
	std::ifstream file;
public:

	XmlParser(void);
	~XmlParser(void);
	void openFile(char *filename);
	void closeFile(void);
	char *getNextTagName(void);
	char *getTagAttributes(char * tagName);
};
