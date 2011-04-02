#pragma once
#include <string>

class XmlAttribute
{
private:
	std::string key, value;
public:
	XmlAttribute(void);
	XmlAttribute(std::string key, std::string value);
	std::string getKey(void) const;
	std::string getValue(void) const;
	~XmlAttribute(void);
};
