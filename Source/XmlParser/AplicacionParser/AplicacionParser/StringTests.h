#pragma once
#include <string>

class StringTests
{
public:
	StringTests(void);
	~StringTests(void);
	void run(void);
	void printResult(std::string testName, bool result);
	void printLeaks(int leaks);
	bool testCreatedStringIsEqualToTemporaryStringIfTheyAreEqual(void);
	bool testCreatedStringIsNotEqualToTemporaryStringIfTheyAreNotEqual(void);
	bool testCreatedEmptyStringIsEqualToEmptyString(void);
};
