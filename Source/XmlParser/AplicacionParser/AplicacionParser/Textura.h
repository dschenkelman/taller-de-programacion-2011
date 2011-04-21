#pragma once
#include "XmlElement.h"
#include <string>

class Textura
{
	bool tieneError;
	List<std::string> validAttributes;
	std::string nombre;
	std::string path;
	int left;
	int top;
	int bottom;
	int right;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement&);
	void getNameFromElement(XmlElement&);
	void getPathFromElement(XmlElement&);
	void getBoundsFromElement(XmlElement&);
public:
	Textura(void);
	Textura(XmlElement& element);
	std::string getNombre(void);
	std::string getPath(void);
	int getLeft(void);
	int getTop(void);
	int getBottom(void);
	int getRight(void);
	bool hasError(void);
	~Textura(void);
};
