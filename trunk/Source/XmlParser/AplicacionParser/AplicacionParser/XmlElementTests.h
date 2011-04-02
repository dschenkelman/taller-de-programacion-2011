#pragma once
#include <string>

// WIP

class XmlElementTests
{
public:
	XmlElementTests(void);
	void run(void);
	void printResult(std::string testName, bool result);
	void printLeaks(int leaks);
	bool initialConstructionTest(void);
	bool testGetChildren(void);
	bool testGetChildrenWithoutAnyChildThrowsException(void);
	bool testHasChildrenWithoutAnyChildReturnsFalse(void);
	bool testGetNameGetStartLineAndEndLineWorkCorrectly(void);
	bool testCopyConstructorWorksCorrectlyWithNoChildElements(void);
	bool testAssignmentOperatorWorkCorrectlyWithNoChildElements(void);
	bool testAssignmentOperatorWorkCorrectlyWithChildElements(void);
	bool testAssignmentOperatorWorkCorrectlyWithAttributes(void);
	~XmlElementTests(void);
};
