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
	bool testCanCompareStringThatAreEqualAndReturnEqual(void);
	bool testCreatedStringIsNotEqualToAnotherStringIfTheyAreNotEqual(void);
	bool testCorrectlyComparesTwoEmptyStrings(void);
	bool testReturnsCorrectStringLength(void);
	bool testCharacterAtIndexCanBeAccessedForReadPurposes(void);
	bool testCharacterAtIndexCanBeAccessedForWritePurposes(void);
	bool testElementAtNonExistingIndexThrowsExceptionWhenAccessedThroughSubscripting(void);
	bool testContainsForSingleCharReturnsCorrectResult(void);
	bool testFindForSingleCharReturnsCorrectIndex(void);
	bool testFindUsingTemporaryStringReturnsCorrectIndex(void);
	bool testFindUsingStringReturnsCorrectIndex(void);
	bool testContainsUsingTemporaryStringReturnsCorrectResult(void);
	bool testContainsUsingStringReturnsCorrectResult(void);
	bool testSubstringMethodReturnsExpectedResultsWithValidStartingIndex(void);
	bool testSubstringMethodThrowsExceptionWithNotValidIndex(void);
	bool testSubstringMethodReturnsExpectedResultsWithValidStartingIndexAndAmountOfElements(void);
	bool testSubstringMethodThrowsExceptionWithNotValidStartingIndex(void);
};

