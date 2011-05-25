#include "SQLite.h"
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#pragma once

using namespace std;

class SQLiteTests
{
public:
	SQLiteTests(void);
	void printLeaks(int leaks);
	void printResult(std::string testName, bool result);
	void run(void);
	bool testCreateDatabaseSuccesfulyCreated();
	bool testRemoveDatabaseSuccesfulyRemoved();
	bool testRemoveNonExistentDatabaseReturnsFalse();
	~SQLiteTests(void);
};
