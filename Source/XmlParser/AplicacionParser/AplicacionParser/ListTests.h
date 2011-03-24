#include <string>

#pragma once

class ListTests
{
public:
	ListTests(void);
	~ListTests(void);
	void run (void);
	void printResult(std::string testName, bool result);
	void ListTests::printLeaks(int leaks);
	bool testListIsCreatedWithNoElements(void);
	bool testThatOneItemShouldBeAdded(void);
	bool testThatCanAddTwoItems(void);
	bool testCanAddFiveItems(void);
	bool testCanAddElevenItems(void);
	bool testThrowsExceptionWhenAccessingElementAtInvalidIndex(void);
	bool testCanRemoveLastItemWhenOnlyOneWasAdded(void);
	bool testCanRemoveAndAddItemsAfterwards(void);
	bool testCapacityIsIncreasedWhenSpaceIsRequired(void);
	bool testCapacityIsDecreasedWhenCanBeReleased(void);
	bool testThrowsExceptionWhenRemovingNonExistingItems(void);
	bool testThrowsExceptionWhenRemovingElementAtPositionOutsideOfBounds(void);
	bool testRemovesElementAtProvidedPosition(void);
	bool testDecreasesLengthWhenRemoveAtIsCalled(void);
	bool testRemovingElementAtZeroWorks(void);
};