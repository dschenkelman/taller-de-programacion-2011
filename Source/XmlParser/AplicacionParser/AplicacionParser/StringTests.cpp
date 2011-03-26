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
	bool successCondition = s == "TestString";
	return successCondition;
}

bool StringTests::testCreatedStringIsNotEqualToTemporaryStringIfTheyAreNotEqual(void)
{
	String s("TestString");
	bool successCondition1 = !(s == "TestStrong");

	bool successCondition2 = !(s == "TestStringer");

	bool successCondition3 = !(s == "Testing");
	return successCondition1 && successCondition2 && successCondition3;
}

bool StringTests::testCreatedEmptyStringIsEqualToEmptyString(void)
{
	String s("");
	bool successCondition = s == "";
	return successCondition;
}

bool StringTests::testCanCompareStringThatAreEqualAndReturnEqual(void)
{
	String s1("TestString");
	String s2("TestString");

	bool successCondition = (s1 == s2);
	return successCondition;
}

bool StringTests::testCreatedStringIsNotEqualToAnotherStringIfTheyAreNotEqual(void)
{
	String s("TestString");
	String s1("TestStrong");
	bool successCondition1 = !(s == s1);

	String s2("TestStringer");
	bool successCondition2 = !(s == s2);

	String s3("Testing");
	bool successCondition3 = !(s == s3);
	return successCondition1 && successCondition2 && successCondition3;
}

bool StringTests::testCorrectlyComparesTwoEmptyStrings(void)
{
	String s1("");
	String s2("");

	bool successCondition = (s1 == s2);

	return successCondition;
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