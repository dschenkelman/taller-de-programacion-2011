#pragma once
#include <string>

class StackTests
{
public:
	StackTests(void);
	~StackTests(void);
	void run (void);
	void printResult(std::string testName, bool result);
	void printLeaks(int leaks);
	bool testCreatedStackIsEmpty(void);
	bool testPushingOneItemToStackMakesItNonEmpty(void);
	bool testPeekingPushedElementReturnsCorrectValue(void);
	bool testCanPopPushedItems(void);
	bool testPoppingNonExistingItemsThrowsException(void);
	bool testPeekingNonExistingItemsThrowsException(void);
	bool testItemsCountIsCorrectWhenPushingAndPoppingMultipleItems(void);
};
