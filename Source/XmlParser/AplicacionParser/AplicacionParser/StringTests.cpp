#include "StdAfx.h"
#include "StringTests.h"
#include "String.h"
#include <iostream>
#include <exception>
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;


StringTests::StringTests(void)
{
}

StringTests::~StringTests(void)
{
}

void StringTests::run(void)
{
	printResult("testCreatedStringIsEqualToTemporaryStringIfTheyAreEqual", testCreatedStringIsEqualToTemporaryStringIfTheyAreEqual());
	printResult("testCreatedStringIsNotEqualToTemporaryStringIfTheyAreNotEqual", testCreatedStringIsNotEqualToTemporaryStringIfTheyAreNotEqual());
	printResult("testCreatedEmptyStringIsEqualToEmptyString", testCreatedEmptyStringIsEqualToEmptyString());
	printResult("testCanCompareStringThatAreEqualAndReturnEqual", testCanCompareStringThatAreEqualAndReturnEqual());
	printResult("testCreatedStringIsNotEqualToAnotherStringIfTheyAreNotEqual", testCreatedStringIsNotEqualToAnotherStringIfTheyAreNotEqual());
	printResult("testCorrectlyComparesTwoEmptyStrings", testCorrectlyComparesTwoEmptyStrings());
	printResult("testReturnsCorrectStringLength", testReturnsCorrectStringLength());
	printResult("testCharacterAtIndexCanBeAccessedForReadPurposes", testCharacterAtIndexCanBeAccessedForReadPurposes());
	printResult("testCharacterAtIndexCanBeAccessedForWritePurposes", testCharacterAtIndexCanBeAccessedForWritePurposes());
	printResult("testElementAtNonExistingIndexThrowsExceptionWhenAccessedThroughSubscripting", testElementAtNonExistingIndexThrowsExceptionWhenAccessedThroughSubscripting());

	//dump memory leaks to VS Output Window
	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

void StringTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

void StringTests::printLeaks(int leaks)
{
	std::cout << "String Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

bool StringTests::testCreatedStringIsEqualToTemporaryStringIfTheyAreEqual(void)
{
	String s("TestString");
	bool successCondition1 = s == "TestString";
	bool successCondition2 = !(s != "TestString");
	return successCondition1 && successCondition2;
}

bool StringTests::testCreatedStringIsNotEqualToTemporaryStringIfTheyAreNotEqual(void)
{
	String s("TestString");
	bool successCondition1 = !(s == "TestStrong");
	bool successCondition2 = (s != "TestStrong");

	bool successCondition3 = !(s == "TestStringer");
	bool successCondition4 = (s != "TestStringer");

	bool successCondition5 = !(s == "Testing");
	bool successCondition6 = (s != "Testing");
	return successCondition1 && successCondition2 && successCondition3
		&& successCondition4 && successCondition5 && successCondition6;
}

bool StringTests::testCreatedEmptyStringIsEqualToEmptyString(void)
{
	String s("");
	bool successCondition1 = s == "";
	bool successCondition2 = !(s != "");
	return successCondition1 && successCondition2;
}

bool StringTests::testCanCompareStringThatAreEqualAndReturnEqual(void)
{
	String s1("TestString");
	String s2("TestString");

	bool successCondition1 = (s1 == s2);
	bool successCondition2 = !(s1 != s2);
	return successCondition1 && successCondition2;
}

bool StringTests::testCreatedStringIsNotEqualToAnotherStringIfTheyAreNotEqual(void)
{
	String s("TestString");
	String s1("TestStrong");
	bool successCondition1 = !(s == s1);
	bool successCondition4 = (s != s1);

	String s2("TestStringer");
	bool successCondition2 = !(s == s2);
	bool successCondition5 = (s != s2);

	String s3("Testing");
	bool successCondition3 = !(s == s3);
	bool successCondition6 = (s != s3);
	return successCondition1 && successCondition2 && successCondition3
		&& successCondition4 && successCondition5 && successCondition6;
}

bool StringTests::testCorrectlyComparesTwoEmptyStrings(void)
{
	String s1("");
	String s2("");

	bool successCondition1 = (s1 == s2);
	bool successCondition2 = !(s1 != s2);

	return successCondition1 && successCondition2;
}

bool StringTests::testReturnsCorrectStringLength(void)
{
	String s1("TestString");
	bool successCondition1 = (s1.length() == 10);

	String s2("");
	bool successCondition2 = (s2.length() == 0);

	String s3("Some longer string to test the size for. It's size is 57.");
	bool successCondition3 = (s3.length() == 57);

	return successCondition1 && successCondition2 && successCondition3;
}

bool StringTests::testCharacterAtIndexCanBeAccessedForReadPurposes(void)
{
	String s("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	bool successCondition = true;

	for (int i = 65; i < 91; i++)
	{
		successCondition = successCondition && s[i - 65] == i;
	}

	return successCondition;
}

bool StringTests::testCharacterAtIndexCanBeAccessedForWritePurposes(void)
{
	String s("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	bool successCondition = true;

	for (int i = 0; i < 26; i++)
	{
		s[i] = '*';
	}

	for (int i = 0; i < 26; i++)
	{
		successCondition = successCondition && s[i] == '*';
	}

	return successCondition;
}

bool StringTests::testElementAtNonExistingIndexThrowsExceptionWhenAccessedThroughSubscripting(void)
{
	String s("TestString");
	bool successCondition1 = false;
	bool successCondition2 = false;

	try
	{
		char a = s[12];
	}
	catch (exception& e)
	{
		successCondition1 = true;
	}

	try
	{
		s[15] = 't';
	}
	catch (exception& e)
	{
		successCondition2 = true;
	}

	return successCondition1 && successCondition2;
}