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
	void populateChildrenFromList(List<XmlElement>& children);
public:
	XmlElement(const std::string name, int start_line, int end_line);
	XmlElement(void);
	XmlElement::XmlElement(XmlElement& other);
	std::string getName(void) const;
	List<XmlElement> getChildren() const;
	void addChild(const XmlElement& child);
	bool addAttribute(const XmlAttribute& attribute);
	bool hasAttribute(const std::string key) const;
	bool hasChildren() const;
	int getStartLine() const;
	int getEndLine() const;
	XmlElement& operator=(const XmlElement& other);
	std::string getValue(std::string key) const;
	~XmlElement(void);
};
