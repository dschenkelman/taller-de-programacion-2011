#include "StdAfx.h"
#include "XmlElement.h"
#include "XmlAttribute.h"
#include "List.h"
using namespace std;

XmlElement::XmlElement(const std::string& n, int startLine, int endLine) : name(n), start_line(startLine), end_line(endLine), children_created(false)
{
}

XmlElement::XmlElement(void) : children_created(false)
{
	
}

XmlElement::XmlElement(const XmlElement& other) {
	this->name = other.name;
	this->start_line = other.start_line;
	this->end_line = other.end_line;

	for(size_t i = 0; i < other.attributes.length(); i++)
	{
		this->attributes.add(other.attributes.at(i));
	}

	if (other.children_created == true) {
		this->children = new List<XmlElement>;

		for (size_t i = 0; i < other.getChildren().length(); i++){
			this->children->add(other.getChildren().at(i));
		}

		this->children_created = true;
	}
	else
	{
		this->children_created = false;
	}
}

string XmlElement::getName() const {
	return this->name;
}

List<XmlElement> XmlElement::getChildren() const {
	if(!this->children_created) {
		throw std::exception();
	}

	return List<XmlElement>(*(this->children));
}

List<XmlAttribute> XmlElement::getAttributes() const
{
	return this->attributes;
}
	
void XmlElement::addChild(const XmlElement& child) {
	if (!this->children_created) {
		this->children_created = true;
		this->children = new List<XmlElement>;
	}
	this->children->add(child);
}

bool XmlElement::hasAttribute(const string& key) const {
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

bool XmlElement::addAttribute(const XmlAttribute& attribute) {
	if (this->hasAttribute(attribute.getKey())) {
		return false;
	}
	this->attributes.add(attribute);
	return true;
}

string XmlElement::getValue(const string& key) const {
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

bool XmlElement::hasChildren() const
{
	return this->children_created && this->children->length() > 0;
}

int XmlElement::getStartLine() const
{
	return this->start_line;
}

int XmlElement::getEndLine() const
{
	return this->end_line;
}

XmlElement& XmlElement::operator=(const XmlElement& other)
{
	if (this == &other) 
	{
		return *this;
	}
	
	// delete children
	if (this->children_created)
	{
		delete this->children;
	}
	
	// initialize
	this->name = other.getName();
	this->start_line = other.getStartLine();
	this->end_line = other.getEndLine();
	this->attributes = other.attributes;
	
	if (other.children_created)
	{
		this->children_created = true;
		this->children = new List<XmlElement>();
		this->populateChildrenFromList(other.getChildren());
	}
	else
	{
		this->children_created = false;
	}

	return *this;
}

//private method
void XmlElement::populateChildrenFromList(List<XmlElement>& elements)
{
	for (size_t i = 0; i < elements.length(); i++)
	{
		this->children->add(elements.at(i));
	}	
}

void XmlElement::setEndLine(int n)
{
	this->end_line = n;
}

XmlElement::~XmlElement(void)
{
	if (this->children_created) {
		delete this->children;
	}
}