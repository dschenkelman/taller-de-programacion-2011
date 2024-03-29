#pragma once
#include "List.h"

class String
{
private:
	static const char END_CHAR = '\0';
	List<char> characters;
	void copyToCharacters(const char* s);
	bool equals(const char*) const;
	bool equals(String&) const;

public:
	String();
	String(char);
	String(const char*);
	~String(void);
	bool operator==(const char*) const;
	bool operator==(String&) const;
	bool operator!=(const char*) const;
	bool operator!=(String&) const;
	char& operator[](size_t) const;
	bool contains(char) const;
	bool contains(const char*) const;
	bool contains(String&) const;
	long find(char) const;
	long find(const char*) const;
	long find(const String&) const;
	size_t length(void) const;
	String substring(size_t startIndex) const;
	String substring(size_t startIndex, size_t len) const;
	List<String> split(char) const;
	List<String> split(const char*) const;
	List<String> split(String&) const;
};
