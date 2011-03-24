#include "StdAfx.h"
#include "xmlValidator.h"
#include <stack>
#include <ctype.h>


xmlValidator::xmlValidator(void)
{
	
}


xmlValidator::~xmlValidator(void)
{
}

bool xmlValidator::validate(string xml)
{
	stack<char> openingChars;
	stack<string> elementNames;
	
	if (xml.at(0) != '<' || xml.at(xml.length() - 1) != '>')
	{
		return false;
	}

	size_t len = xml.length();

	for (size_t i = 0; i < len; i++)
	{
		char currentChar = xml.at(i);
		if (currentChar == '<')
		{
			char nextChar = xml.at(i+1);
			if (!openingChars.empty() || nextChar == ' ' || !(isalpha(nextChar) || nextChar == '_' || nextChar == '?' || nextChar == '/'))
			{
				//cannot have < ElementName ...>
				return false;
			}

			if (isalpha(nextChar) || nextChar == '_')
			{
				elementNames.push(getOpeningElementName(xml, &i));
			}

			if (nextChar == '/')
			{
				string closingElementName = getClosingElementName(xml, &i);
				string openingElementName = elementNames.top();
				if (openingElementName != closingElementName)
				{
					return false;
				}

				elementNames.pop();
			}

			openingChars.push(currentChar);
		}

		if (currentChar == '"')
		{
			if (openingChars.top() == '"')
			{
				openingChars.pop();
			}
			else
			{
				openingChars.push(currentChar);
			}
		}
		

		if (currentChar == '>')
		{
			if (openingChars.empty() || openingChars.top() != '<') return false;
			openingChars.pop();
		}
	}	
	
	return true;
}

string xmlValidator::getOpeningElementName(string xml, size_t* index)
{
	size_t initialIndex= (*index) + 1;
	size_t endNameIndex = xml.find_first_of(" />", *index);
	*index = (endNameIndex - 1);
	return xml.substr(initialIndex, endNameIndex - initialIndex);
}

string xmlValidator::getClosingElementName(string xml, size_t* index)
{
	size_t initialIndex= (*index) + 2;
	size_t endNameIndex = xml.find_first_of(" >", *index);
	*index = (endNameIndex - 1);
	return xml.substr(initialIndex, endNameIndex - initialIndex);
}