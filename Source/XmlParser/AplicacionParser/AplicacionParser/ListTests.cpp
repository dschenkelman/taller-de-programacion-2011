#include "StdAfx.h"
#include "List.h"
#include "ListTests.h"
#include <iostream>
#include <exception>
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

ListTests::ListTests(void)
{
}

ListTests::~ListTests(void)
{
}

void ListTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed\n"));
}

void ListTests::printLeaks(int leaks)
{
	std::cout << "Hubo " << leaks << " memory leaks.";
}

void ListTests::run()
{
	printResult("testListIsCreatedWithNoElements", testListIsCreatedWithNoElements());
	printResult("testThatOneItemShouldBeAdded", testThatOneItemShouldBeAdded());
	printResult("testThatCanAddTwoItems", testThatCanAddTwoItems());
	printResult("testCanAddFiveItems", testCanAddFiveItems());
	printResult("testCanAddElevenItems", testCanAddElevenItems());
	printResult("testThrowsExceptionWhenAccessingElementAtInvalidIndex", testThrowsExceptionWhenAccessingElementAtInvalidIndex());
	printResult("testCanRemoveLastItemWhenOnlyOneWasAdded", testCanRemoveLastItemWhenOnlyOneWasAdded());

	//dump memory leaks to VS Output Window
	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

bool ListTests::testListIsCreatedWithNoElements(void)
{
	List<int> list;
	size_t len = list.length();
	bool successCondition1 = (len == 0);
	return successCondition1;
}

bool ListTests::testThatOneItemShouldBeAdded(void)
{
	List<int> list;
	list.add(5);
	bool successCondition1 = (list.length() == 1);
	bool successCondition2 = (list.at(0) == 5);
	return successCondition1 && successCondition2;
}

bool ListTests::testThatCanAddTwoItems(void)
{
	List<int> list;
	list.add(5);
	list.add(9);
	bool successCondition1 = (list.length() == 2);
	bool successCondition2 = (list.at(0) == 5);
	bool successCondition3 = (list.at(1) == 9);

	return successCondition1 && successCondition2 && successCondition3;
}

bool ListTests::testCanAddFiveItems(void)
{
	List<int> list;
	list.add(5);
	list.add(6);
	list.add(7);
	list.add(8);
	list.add(9);
	bool successCondition1 = (list.length() == 5);
	bool successCondition2 = (list.at(0) == 5);
	bool successCondition3 = (list.at(1) == 6);
	bool successCondition4 = (list.at(2) == 7);
	bool successCondition5 = (list.at(3) == 8);
	bool successCondition6 = (list.at(4) == 9);

	return successCondition1 && successCondition2 && successCondition3
		&& successCondition4 && successCondition5 && successCondition6;
}

bool ListTests::testCanAddElevenItems(void)
{
	List<int> list;
	for (int i = 0; i < 11; i++)
	{
		list.add(i);	
	}
	bool successCondition = (list.length() == 11);

	for (int i = 0; i < 11; i++)
	{
		successCondition == successCondition && list.at(i);	
	}
	return successCondition;
}
bool ListTests::testThrowsExceptionWhenAccessingElementAtInvalidIndex(void)
{
	List<int> list;
	list.add(5);
	list.add(4);
	list.add(3);
	bool successCondition1 = false;
	bool successCondition2 = false;

	try
	{
		list.at(3);
	}
	catch (exception& e)
	{
		successCondition1 = true;
	}

	try
	{
		list.at(-1);
	}
	catch (exception& e)
	{
		successCondition2 = true;
	}

	return successCondition1 && successCondition2;
}


bool ListTests::testCanRemoveLastItemWhenOnlyOneWasAdded(void)
{
	List<int> list;
	list.add(5);
	list.removeLast();
	bool successCondition1 = list.length() == 0;
	bool successCondition2 = false;
	
	try
	{
		list.at(0);
	}
	catch (exception& e)
	{
		successCondition2 = true;
	}

	return successCondition1 && successCondition2;
}