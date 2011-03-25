#include "StdAfx.h"
#include "StackTests.h"
#include "Stack.h"
#include <iostream>
#include <exception>
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

StackTests::StackTests(void)
{
}

StackTests::~StackTests(void)
{
}

void StackTests::run()
{
	printResult("testCreatedStackIsEmpty", testCreatedStackIsEmpty());
	printResult("testPushingOneItemToStackMakesItNonEmpty", testPushingOneItemToStackMakesItNonEmpty());
	printResult("testPeekingPushedElementReturnsCorrectValue", testPeekingPushedElementReturnsCorrectValue());
	printResult("testCanPopPushedItems", testCanPopPushedItems());
	printResult("testPoppingNonExistingItemsThrowsException", testPoppingNonExistingItemsThrowsException());
	printResult("testPeekingNonExistingItemsThrowsException", testPeekingNonExistingItemsThrowsException());
	printResult("testItemsCountIsCorrectWhenPushingAndPoppingMultipleItems", testItemsCountIsCorrectWhenPushingAndPoppingMultipleItems());
	
	//dump memory leaks to VS Output Window
	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

void StackTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

void StackTests::printLeaks(int leaks)
{
	std::cout << "Stack Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

bool StackTests::testCreatedStackIsEmpty(void)
{
	Stack<int> stack;
	bool successCondition = stack.count() == 0;

	return successCondition;
}

bool StackTests::testPushingOneItemToStackMakesItNonEmpty(void)
{
	Stack<int> stack;
	stack.push(5);
	bool successCondition = stack.count() == 1;

	return successCondition;
}

bool StackTests::testPeekingPushedElementReturnsCorrectValue(void)
{
	Stack<int> stack;
	stack.push(5);
	bool successCondition1 = stack.peek() == 5;
	
	stack.push(6);
	bool successCondition2 = stack.peek() == 6;

	bool successCondition3 = stack.count() == 2;

	return successCondition1 && successCondition2 && successCondition3;
}

bool StackTests::testCanPopPushedItems(void)
{
	Stack<int> stack;
	stack.push(5);
	stack.push(6);
	stack.push(7);

	bool successCondition1 = stack.pop() == 7;
	bool successCondition2 = stack.pop() == 6;
	bool successCondition3 = stack.pop() == 5;

	return successCondition1 && successCondition2 && successCondition3;
}

bool StackTests::testPoppingNonExistingItemsThrowsException(void)
{
	Stack<int> stack;
	bool successCondition = false;

	try
	{
		stack.pop();
	}
	catch (exception& e)
	{
		successCondition = true;
	}

	return successCondition;
}

bool StackTests::testPeekingNonExistingItemsThrowsException(void)
{
	Stack<int> stack;
	bool successCondition = false;

	try
	{
		stack.peek();
	}
	catch (exception& e)
	{
		successCondition = true;
	}

	return successCondition;
}

bool StackTests::testItemsCountIsCorrectWhenPushingAndPoppingMultipleItems(void)
{
	Stack<int> stack;
	bool successCondition = true;
	
	for (int i = 0; i < 100; i++)
	{
		stack.push(i);
		successCondition = successCondition && (stack.count() == i + 1);
	}

	for (int i = 0; i < 100; i++)
	{
		int popped = stack.pop();
		successCondition = successCondition && (popped == 99 - i);
		successCondition = successCondition && (stack.count() == 99 - i);
	}

	return successCondition;
}