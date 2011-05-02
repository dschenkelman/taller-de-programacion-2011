#pragma once
#include <string>

class ImageTests
{
public:
	ImageTests(void);
	~ImageTests(void);
	void run (void);
	void printResult(std::string testName, bool result);
	bool testResizeToSmaller(void);
	bool testResizeToBigger(void);
	void printLeaks(int leaks);
};