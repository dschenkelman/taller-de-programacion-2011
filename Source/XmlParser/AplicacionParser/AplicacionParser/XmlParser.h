#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "List.h"
#include "Logger.h"
#include "XmlElement.h"

#pragma once

class XmlParser
{
private:
	long lineNumber;
	std::ifstream xmlFile;
	std::string lineRead;
	void parseAttribute(std::string attName);
	void parseOpeningLine(std::string line);
	void parseClosingLine(std::string line);
	std::string tagName;
	//Por ahora dejo una lista de strings de la siguiente forma (Clave,Valor,Clave,Valor...)
	List<std::string> tagAtt;
	std::string& preParseString(std::string& context, char char1, char char2 );
	void trim(std::string& str, char c);
	Logger *log;
	bool noChildren;
	bool hasErrors;
	bool isOpeningLine;
	bool isValidTagName(std::string tagName);
	std::string validTags[9];
public:

	XmlParser(void);
	~XmlParser(void);
	void openFile(std::string filename);
	void closeFile(void);
	bool getXmlLine(void);
	std::string getLineTagName(void);
	List<std::string> getLineTagAttributes(void);
	std::string getLineRead(void);
	long getLineNumber(void);
	void parseLine(void);
	bool isFileOpen(void);
	bool tagHasNoChildren(void);
	bool lineHasErrors(void);
	bool getIsOpeningLine(void) const;
	XmlElement parse(void);
};
