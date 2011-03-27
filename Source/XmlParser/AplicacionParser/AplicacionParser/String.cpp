#include "StdAfx.h"
#include "String.h"

String::String(const char* s)
{
	this->copyToCharacters(s);
}

String::~String(void)
{
}

bool String::operator ==(const char* s)
{
	return this->equals(s);
}

bool String::operator ==(String& s)
{
	return this->equals(s);
}

bool String::operator !=(const char* s)
{
	return !this->equals(s);
}

bool String::operator !=(String& s)
{
	return !this->equals(s);
}

size_t String::length(void)
{
	return this->characters.length() - 1;
}

//private methods
void String::copyToCharacters(const char *s)
{
	int i = 0;
	char currentChar = s[0];
	while(currentChar != END_CHAR)
	{
		this->characters.add(currentChar);
		i++;
		currentChar = s[i];
	}
	this->characters.add(END_CHAR);
}

bool String::equals(const char* s)
{
	int i = 0;
	char externalChar = s[i];
	char internalChar = this->characters.at(i);
	while(internalChar != END_CHAR && internalChar != END_CHAR)
	{
		if (internalChar != externalChar)
		{
			return false;
		}

		i++;
		externalChar = s[i];
		internalChar = this->characters.at(i);
	}

	if (externalChar == internalChar)
	{
		return true;
	}

	return false;	
}

bool String::equals(String& s)
{
	int i = 0;
	char externalChar = s.characters.at(i);
	char internalChar = this->characters.at(i);
	while(internalChar != END_CHAR && internalChar != END_CHAR)
	{
		if (internalChar != externalChar)
		{
			return false;
		}

		i++;
		externalChar = s.characters.at(i);
		internalChar = this->characters.at(i);
	}

	if (externalChar == internalChar)
	{
		return true;
	}

	return false;
}