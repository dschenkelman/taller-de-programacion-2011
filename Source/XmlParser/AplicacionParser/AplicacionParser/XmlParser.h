#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

#define LINE_SIZE 200
#pragma once

class XmlParser
{
private:
	long lineNumber;
	FILE *xmlFile;
	char lineRead[LINE_SIZE];
	bool isFileOpen(void);
	void parseAttribute(char *);
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
	void parseLine(void);
};
