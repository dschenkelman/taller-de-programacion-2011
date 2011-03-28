#include "StdAfx.h"
#include "XmlAttribute.h"
using namespace std;

XmlAttribute::XmlAttribute(void)
{
}

XmlAttribute::XmlAttribute(std::string key, std::string value)
{
	this->key = key;
	this->value = value;
}

string XmlAttribute::getKey(void) {
	return this->key;
}

string XmlAttribute::getValue(void) {
	return this->value;
}

XmlAttribute::~XmlAttribute(void)
{
}
