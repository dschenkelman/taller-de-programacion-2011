#pragma once
#include <string>

class TexturaTests
{
public:
	TexturaTests(void);
	void printLeaks(int);
	void run(void);
	void printResult(std::string testName, bool result);
	bool testIsCreatedFromElementWithNameTextura(void);
	bool testHasErrorIfAttributeNameIsNotValid(void);
	~TexturaTests(void);
};
