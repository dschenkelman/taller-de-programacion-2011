#include "StdAfx.h"
#include "XmlElement.h"
#include "XmlAttribute.h"
#include "List.h"
using namespace std;

XmlElement::XmlElement(std::string name, int start_line, int end_line)
{
	this->name = name;
	this->start_line = start_line;
	this->end_line = end_line;
}

void XmlElement::addChild(XmlElement child) {
	this->children.add(child);
}

bool XmlElement::hasAttribute(string key) {
	size_t len_list = this->attributes.length();
	XmlAttribute my_attr;
	for(size_t i=0;i<len_list;i++) {
		my_attr = this->attributes.at(i);
		if (my_attr.getKey() == key) {
			return true;
		}
	}
	return false;
}

bool XmlElement::addAttribute(XmlAttribute attribute) {
	if (this->hasAttribute(attribute.getKey())) {
		return false;
	}
	this->attributes.add(attribute);
	return true;
}

string XmlElement::getValue(string key) {
	size_t len_list = this->attributes.length();
	XmlAttribute my_attr;
	for(size_t i=0;i<len_list;i++) {
		my_attr = this->attributes.at(i);
		if (my_attr.getKey() == key) {
			return my_attr.getValue();
		}
	}
	return "";
}

XmlElement::XmlElement(void) {
}

XmlElement::~XmlElement(void)
{
}
