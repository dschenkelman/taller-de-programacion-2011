#include <string>

#pragma once

class LoggerTests
{
public:
	LoggerTests(void);
	~LoggerTests(void);
	void run (void);
	void printResult(std::string testName, bool result);
	bool testLogWarning(void);
	bool testLogError(void);
};