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
	int red;
	int green;
	int blue;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement&);
	bool validateHex(std::string& hex);
	void getNameFromElement(XmlElement&);
	void getPathFromElement(XmlElement&);
	void getBoundsFromElement(XmlElement&);
	void getAlphaFromElement(XmlElement&);
public:
	Textura(void);
	Textura(XmlElement& element);
	std::string getNombre(void);
	std::string getPath(void);
	int getLeft(void);
	int getTop(void);
	int getBottom(void);
	int getRight(void);
	int getRed(void);
	int getGreen(void);
	int getBlue(void);
	bool hasError(void);
	~Textura(void);
};
