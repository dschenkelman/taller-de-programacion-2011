#pragma once
#include "List.h"

class String
{
private:
	static const char END_CHAR = '\0';
	List<char> characters;
	void copyToCharacters(const char* s);
public:
	String(const char*);
	~String(void);
	bool operator==(const char*);
};
