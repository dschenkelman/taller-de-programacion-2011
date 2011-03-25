#include <iostream>
#include <fstream>
#include <string>
#pragma once

class XmlParser
{
private:
	long lineNumber;
	std::ifstream file;
	char * lineRead;
	std::string line;
public:

	XmlParser(void);
	~XmlParser(void);
	void openFile(char *filename);
	void closeFile(void);
	void getXmlLine(void);
	char * getLineTagName(void);
	char * getLineTagAttributes(char * tagName);
	char * getLineRead(void);
	long getLineNumber(void);
};
