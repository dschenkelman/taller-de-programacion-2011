#pragma once
#include <string>

class BonusTests
{
public:
	BonusTests(void);
	void printLeaks(int);
	void run(void);
	void printResult(std::string testName, bool result);
	bool testNonValidAttributeMakesHasErrorTrue(void);
	~BonusTests(void);
};
