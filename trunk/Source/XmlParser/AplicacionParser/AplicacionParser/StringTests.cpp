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
	String s = String("TestString");
	bool successCondition = s == "TestString";
	return successCondition;
}

bool StringTests::testCreatedStringIsNotEqualToTemporaryStringIfTheyAreNotEqual(void)
{
	String s = String("TestString");
	bool successCondition1 = !(s == "TestStrong");

	bool successCondition2 = !(s == "TestStringer");

	bool successCondition3 = !(s == "Testing");
	return successCondition1 && successCondition2 && successCondition3;
}

bool StringTests::testCreatedEmptyStringIsEqualToEmptyString(void)
{
	String s = String("");
	bool successCondition = s == "";
	return successCondition;
}