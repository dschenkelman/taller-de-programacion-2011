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
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

void ListTests::printLeaks(int leaks)
{
	std::cout << "List Tests: Hubo " << leaks << " memory leaks." << endl << endl;
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
	printResult("testCanRemoveAndAddItemsAfterwards", testCanRemoveAndAddItemsAfterwards());
	printResult("testCapacityIsIncreasedWhenSpaceIsRequired", testCapacityIsIncreasedWhenSpaceIsRequired());
	printResult("testCapacityIsDecreasedWhenCanBeReleased", testCapacityIsDecreasedWhenCanBeReleased());
	printResult("testThrowsExceptionWhenRemovingNonExistingItems",testThrowsExceptionWhenRemovingNonExistingItems());
	printResult("testThrowsExceptionWhenRemovingElementAtPositionOutsideOfBounds", testThrowsExceptionWhenRemovingElementAtPositionOutsideOfBounds());
	printResult("testRemovesElementAtProvidedPosition", testRemovesElementAtProvidedPosition());
	printResult("testDecreasesLengthWhenRemoveAtIsCalled", testDecreasesLengthWhenRemoveAtIsCalled());
	printResult("testRemovingElementAtZeroWorks", testRemovingElementAtZeroWorks());
	printResult("testElementAtIndexCanBeAccessedThroughSubscriptOperatorForReadPurposes", testElementAtIndexCanBeAccessedThroughSubscriptOperatorForReadPurposes());
	printResult("testElementAtIndexCanBeAccessedThroughSubscriptOperatorForWritePurposes", testElementAtIndexCanBeAccessedThroughSubscriptOperatorForWritePurposes());
	printResult("testElementAtNonExistingIndexThrowsExceptionWhenAccessedThroughSubscripting", testElementAtNonExistingIndexThrowsExceptionWhenAccessedThroughSubscripting());
	printResult("testCopyConstructorWorksCorrectly", testCopyConstructorWorksCorrectly());
	printResult("testAssignmentOperatorWorksCorrectly", testAssignmentOperatorWorksCorrectly());
	printResult("testClearRemovesAllElementsFromList", testClearRemovesAllElementsFromList());

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
	int removed = list.removeLast();
	bool successCondition1 = list.length() == 0;
	bool successCondition2 = false;
	bool successCondition3 = removed == 5;
	
	try
	{
		list.at(0);
	}
	catch (exception& e)
	{
		successCondition2 = true;
	}

	return successCondition1 && successCondition2 && successCondition3;
}

bool ListTests::testCanRemoveAndAddItemsAfterwards(void)
{
	List<int> list;
	list.add(5);
	list.add(6);
	list.add(7);
	list.add(8);
	int removed1 = list.removeLast();
	int removed2 = list.removeLast();
	bool successCondition1 = list.length() == 2;
	bool successCondition2 = removed1 == 8;
	bool successCondition3 = removed2 == 7;
	
	list.add(9);
	int removed3 = list.removeLast();
	bool successCondition4 = removed3 == 9;
	return successCondition1 && successCondition2 
		&& successCondition3 && successCondition4;
}

bool ListTests::testCapacityIsIncreasedWhenSpaceIsRequired(void)
{
	List<int> list;
	bool successCondition = list.capacity() == 10;
	
	for (int i = 0; i < 100; i++)
	{
		list.add(i);
		//capacity should increase in multiples of ten
		if (i % 10 	== 0)
		{
			successCondition = successCondition && list.capacity() == 10 + i;
		}
	}

	return successCondition;
}

bool ListTests::testCapacityIsDecreasedWhenCanBeReleased(void)
{
	List<int> list;
	bool successCondition = true;
	
	for (int i = 0; i < 100; i++)
	{
		list.add(i);
	}

	for (int i = 0; i < 100; i++)
	{
		list.removeLast();

		if (i % 10 	== 0)
		{
			successCondition = successCondition && list.capacity() == 100 - i;
		}
	}

	return successCondition;
}

bool ListTests::testThrowsExceptionWhenRemovingNonExistingItems(void)
{
	List<int> list;
	bool successCondition = false;

	try
	{
		list.removeLast();
	}
	catch (exception& e)
	{
		successCondition = true;
	}

	return successCondition;
}


bool ListTests::testThrowsExceptionWhenRemovingElementAtPositionOutsideOfBounds()
{
	List<int> list;
	list.add(1);
	list.add(2);
	list.add(3);
	bool successCondition = false;

	try
	{
		list.removeAt(5);
	}
	catch (exception& e)
	{
		successCondition = true;
	}

	return successCondition;
}

bool ListTests::testRemovesElementAtProvidedPosition(void)
{
	List<int> list;
	list.add(1);
	list.add(2);
	list.add(3);
	int removed = list.removeAt(1);
	bool successCondition1 = removed == 2;
	bool successCondition2 = list.at(0) == 1;
	bool successCondition3 = list.at(1) == 3;
	return successCondition1 && successCondition2 && successCondition3;
}

bool ListTests::testDecreasesLengthWhenRemoveAtIsCalled(void)
{
	List<int> list;
	list.add(1);
	list.add(2);
	list.add(3);
	list.removeAt(1);
	bool successCondition1 = list.length() == 2;
	list.removeAt(1);
	bool successCondition2 = list.length() == 1;
	list.removeAt(0);
	bool successCondition3 = list.length() == 0;
	return successCondition1 && successCondition2 && successCondition3;
}

bool ListTests::testRemovingElementAtZeroWorks(void)
{
	List<int> list;
	list.add(1);
	list.add(2);
	list.add(3);
	list.add(4);

	bool successCondition1 = list.removeAt(0) == 1;
	bool successCondition2 = list.removeAt(0) == 2;
	bool successCondition3 = list.removeAt(0) == 3;
	bool successCondition4 = list.removeAt(0) == 4;

	return successCondition1 && successCondition2 &&
		successCondition3 && successCondition4;
}

bool ListTests::testElementAtIndexCanBeAccessedThroughSubscriptOperatorForReadPurposes(void)
{
	List<int> list;
	bool successCondition = true;

	for (int i = 0; i < 100; i++)
	{
		list.add(i);
	}

	for (int i = 0; i < 100; i++)
	{
		successCondition = successCondition && list[i] == i;
	}

	return successCondition;
}

bool ListTests::testElementAtIndexCanBeAccessedThroughSubscriptOperatorForWritePurposes(void)
{
	List<int> list;
	bool successCondition = true;

	for (int i = 0; i < 100; i++)
	{
		list.add(i);
	}

	for (int i = 100; i > 0; i--)
	{
		int j = 100 - i;
		list[i - 1] = j;
	}

	for (int i = 0; i < 100; i++)
	{
		successCondition = successCondition && list.at(i) == 99 - i;
	}

	return successCondition;
}

bool ListTests::testElementAtNonExistingIndexThrowsExceptionWhenAccessedThroughSubscripting(void)
{
	List<int> list;
	bool successCondition1 = false;
	bool successCondition2 = false;

	list.add(5);
	list.add(6);

	try
	{
		int a = list[4];
	}
	catch (exception& e)
	{
		successCondition1 = true;
	}

	try
	{
		list[8] = 4;
	}
	catch (exception& e)
	{
		successCondition2 = true;
	}

	return successCondition1 && successCondition2;
}

bool ListTests::testCopyConstructorWorksCorrectly(void)
{
	List<int> list1;
	list1.add(5);
	list1.add(6);
	list1.add(7);
	
	List<int> list2(list1);
	bool successCondition1 = list2.at(0) == 5;
	bool successCondition2 = list2.at(1) == 6;
	bool successCondition3 = list2.at(2) == 7;
	bool successCondition4 = list2.length() == 3;

	return successCondition1 && successCondition2 && successCondition3 && successCondition4;
}

bool ListTests::testAssignmentOperatorWorksCorrectly(void)
{
	List<int> list1;	
	List<int> list2;

	list1.add(5);
	list1.add(6);
	list1.add(7);
	list2.add(1);
	list2.add(2);
	list2.add(3);
	list2.add(4);

	list1 = list2;

	bool successCondition1 = list1.at(0) == 1;
	bool successCondition2 = list1.at(1) == 2;
	bool successCondition3 = list1.at(2) == 3;
	bool successCondition4 = list1.at(3) == 4;
	bool successCondition5 = list1.length() == 4;

	return successCondition1 && successCondition2 &&
			successCondition3 && successCondition4 &&
			successCondition5;
}

bool ListTests::testClearRemovesAllElementsFromList(void)
{
	List<int> list;
	
	list.add(5);
	list.add(6);
	list.add(7);
	list.clear();

	bool successCondition = list.length() == 0;

	return successCondition;
}