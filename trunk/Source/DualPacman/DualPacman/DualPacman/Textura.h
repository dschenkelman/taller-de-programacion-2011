#pragma once
#include "XmlElement.h"
#include <string>

class Textura
{
	bool tieneError;
	List<std::string> validAttributes;
	std::string nombre;
	std::string path;
	bool usada;
	int line;
	int left;
	int top;
	int bottom;
	int right;
	int red;
	int green;
	int blue;
	int delta;
	int rotation;
	void populateValidAttributes(void);
	bool validateAttributes(XmlElement&);
	bool validateHex(std::string& hex);
	void getNameFromElement(XmlElement&);
	void getPathFromElement(XmlElement&);
	void getBoundsFromElement(XmlElement&);
	void getAlphaFromElement(XmlElement&);
	void getDeltaFromElement(XmlElement&);
	void getRotationFromElement(XmlElement&);
public:
	Textura(void);
	Textura(std::string imagePath);
	Textura(XmlElement& element);
	std::string getNombre(void);
	void setNombre(std::string);
	std::string getPath(void);
	int getLeft(void);
	int getTop(void);
	int getBottom(void);
	int getRight(void);
	int getRed(void);
	int getGreen(void);
	int getBlue(void);
	int getDelta(void);
	int getRotation(void);
	bool hasError(void);
	void setLine(int);
	int getLine(void);
	void use(void);
	bool isUsed(void);
	~Textura(void);
};
