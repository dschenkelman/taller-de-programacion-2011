#include "StdAfx.h"
#include "XmlAttribute.h"
using namespace std;

XmlAttribute::XmlAttribute(void)
{
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
