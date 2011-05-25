#include <iostream>
#include "SQLite.h"
#include "SQLiteTests.h"
#include "QueryTests.h"
#include "DatabaseTests.h"
#include "sqlite/sqlite3.h"
#pragma once

using namespace std;

void runTests()
{
	cout << "SQLITE TESTS" << endl << endl;
	SQLiteTests sqltests;
	sqltests.run();

	cout << endl;
	cout << "QUERY TESTS" << endl << endl;
	QueryTests queryTests;
	queryTests.run();

	cout << endl;
	cout << "DATABASE TESTS" << endl << endl;
	DatabaseTests databaseTests;
	databaseTests.run();
}

int main(char argc, char* argv[])
{
	runTests();

	char c;
	c = getchar();
}