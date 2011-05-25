#include "SQLite.h"
#include <string>
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#pragma once

class QueryTests
{
public:
	QueryTests(void);
	void printLeaks(int leaks);
	void printResult(std::string testName, bool result);
	void run(void);
	bool testExecuteQueryWithoutResults();
	bool testExecuteQueryWithResults();
	~QueryTests(void);
};
