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
	~XmlElementTests(void);
};
