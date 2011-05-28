#include "StdAfx.h"
#include "XmlAttribute.h"
using namespace std;

XmlAttribute::XmlAttribute(void)
{
}

XmlAttribute::XmlAttribute(const std::string& k, const std::string& v) : key(k), value(v)
{
}

string XmlAttribute::getKey(void) const {
	return this->key;
}

string XmlAttribute::getValue(void) const {
	return this->value;
}

XmlAttribute::~XmlAttribute(void)
{
}
