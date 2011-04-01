#pragma once
#include <string>
#include "List.h"
#include "XmlAttribute.h"

class XmlElement
{
private:
	std::string name;
	int start_line, end_line;
	List<XmlElement>* children;
	bool children_created;
	List<XmlAttribute> attributes;
public:
	XmlElement(std::string name, int start_line, int end_line);
	XmlElement(void);
	XmlElement::XmlElement(XmlElement& other);
	std::string getName(void);
	List<XmlElement> getChildren();
	void addChild(XmlElement& child);
	bool addAttribute(XmlAttribute& attribute);
	bool hasAttribute(std::string key);
	bool hasChildren();
	int getStartLine();
	int getEndLine();
	std::string getValue(std::string key);
	~XmlElement(void);
};
