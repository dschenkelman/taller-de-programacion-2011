#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include "List.h"
#include "String.h"

#define LINE_SIZE 200
#pragma once

class XmlParser
{
private:
	long lineNumber;
	FILE *xmlFile;
	char lineRead[LINE_SIZE];
	void parseAttribute(char *);
	String tagName;
	//Por ahora dejo una lista de strings de la siguiente forma (Clave,Valor,Clave,Valor...)
	List<String> tagAtt;

public:

	XmlParser(void);
	~XmlParser(void);
	void openFile(char *filename);
	void closeFile(void);
	bool getXmlLine(void);
	String getLineTagName(void);
	List<String> getLineTagAttributes(void);
	char * getLineRead(void);
	long getLineNumber(void);
	void parseLine(void);
	bool isFileOpen(void);
};
