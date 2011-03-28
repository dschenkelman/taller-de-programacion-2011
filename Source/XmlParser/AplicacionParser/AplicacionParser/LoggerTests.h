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
	bool LoggerTests::testLogWarningConstructorSoloRuta(void);
	bool testLogError(void);
	bool LoggerTests::testLogErrorConstructorSoloRuta(void);
	void printLeaks(int leaks);
};