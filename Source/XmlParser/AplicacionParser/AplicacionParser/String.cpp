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
	int i = 0;
	char externalChar = s[i];
	char internalChar = this->characters[i];
	while(internalChar != END_CHAR && internalChar != END_CHAR)
	{
		if (internalChar != externalChar)
		{
			return false;
		}

		i++;
		externalChar = s[i];
		internalChar = this->characters[i];
	}

	if (externalChar == internalChar)
	{
		return true;
	}

	return false;
}

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