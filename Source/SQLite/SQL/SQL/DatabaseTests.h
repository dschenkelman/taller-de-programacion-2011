#include "Database.h"
#include <string>
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#pragma once

class DatabaseTests
{
public:
	DatabaseTests(void);
	void printLeaks(int leaks);
	void printResult(std::string testName, bool result);
	void run(void);
	bool testCreateTableSuccesfulyCreated();
	bool testInsertData();
	bool testUpdateData();
	~DatabaseTests(void);
};
