#include "StdAfx.h"
#include "String.h"

String::String(const char* s)
{
	this->copyToCharacters(s);
}

String::~String(void)
{
}

bool String::operator ==(const char* s) const
{
	return this->equals(s);
}

bool String::operator ==(String& s) const
{
	return this->equals(s);
}

bool String::operator !=(const char* s) const
{
	return !this->equals(s);
}

bool String::operator !=(String& s) const
{
	return !this->equals(s);
}

char& String::operator [](size_t index) const
{
	return this->characters.at(index);
}

size_t String::length(void) const
{
	return this->characters.length() - 1;
}

bool String::contains(char c) const
{
	return this->find(c) != -1;
}

bool String::contains(const char* s) const
{
	return this->find(s) != -1;
}

bool String::contains(String& s) const
{
	return this->find(s) != -1;
}

long String::find(char c) const
{
	for (size_t i = 0; i < this->characters.length(); i++)
	{
		if (this->characters.at(i) == c)
		{
			return i;
		}
	}

	return -1;
}

long String::find(const char* s) const
{
	return this->find(String(s));
}

long String::find(const String& otherString) const
{
	size_t itemsToFind = otherString.length();
	size_t itemsFound = 0;
	size_t initialIndex = 0;
	for (size_t i = 0; i < this->length(); i++)
	{		
		if (this->characters.at(i) == otherString[itemsFound])
		{
			if (itemsFound == 0)
			{
				initialIndex = i;
			}
			itemsFound++;
		}
		else
		{
			itemsFound = 0;
		}

		if (itemsFound == itemsToFind)
		{
			return initialIndex;
		}
	}

	return -1;
}

String String::substring(size_t startIndex) const
{
	return this->substring(startIndex, this->length() - startIndex);
}

String String::substring(size_t startIndex, size_t subLen) const
{
	if (startIndex >= this->length())
	{
		throw std::exception();
	}
	
	String aux;
	size_t end = (startIndex + subLen) < this->length() ? (startIndex + subLen) : this->length();
	for (size_t i = startIndex; i < end; i++)
	{
		aux.characters.add(this->characters.at(i));
	}

	aux.characters.add(END_CHAR);

	return aux;
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

bool String::equals(const char* s) const
{
	String aux(s);
	return this->equals(aux);
}

bool String::equals(String& s) const
{
	if (s.length() != this->length())
	{
		return false;
	}
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

String::String()
{

}