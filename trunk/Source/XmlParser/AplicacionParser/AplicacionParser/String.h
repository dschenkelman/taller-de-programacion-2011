#pragma once
#include "List.h"

class String
{
private:
	static const char END_CHAR = '\0';
	List<char> characters;
	void copyToCharacters(const char* s);
	bool equals(const char*);
	bool equals(String&);
public:
	String(const char*);
	~String(void);
	bool operator==(const char*);
	bool operator==(String&);
	bool operator!=(const char*);
	bool operator!=(String&);
	char& operator[](size_t);
	size_t length(void);
};
