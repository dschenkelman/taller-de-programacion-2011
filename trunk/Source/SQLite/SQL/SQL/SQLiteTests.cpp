#include "SQLiteTests.h"
#include "SQLiteTests.h"
#include "Database.h"
#include <iostream>
#include <string>
#include <exception>

using namespace std;

SQLiteTests::SQLiteTests(void)
{
}

void SQLiteTests::printLeaks(int leaks)
{
	std::cout << "Bonus Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

void SQLiteTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

void SQLiteTests::run()
{
	printResult("testCreateDatabaseSuccesfulyCreated", testCreateDatabaseSuccesfulyCreated());
	printResult("testRemoveDatabaseSuccesfulyRemoved", testRemoveDatabaseSuccesfulyRemoved());
	printResult("testRemoveNonExistentDatabaseReturnsFalse", testRemoveNonExistentDatabaseReturnsFalse());

    int leaks = _CrtDumpMemoryLeaks();
    printLeaks(leaks);
}

bool SQLiteTests::testCreateDatabaseSuccesfulyCreated()
{
	SQLite sql;
	sql.createDatabase("SQLiteTests01.db");
	
	Database db = sql.getDatabase("SQLiteTests01.db");

	if(!(db.getName() == "SQLiteTests01.db"))
	{
		return false;
	}
	
	// elimina la base de datos y el archivo .db
	db.deleteDatabase();
	return true;
}

bool SQLiteTests::testRemoveDatabaseSuccesfulyRemoved()
{
	SQLite sql;
	sql.createDatabase("SQLiteTests02.db");
	
	Database db = sql.getDatabase("SQLiteTests02.db");

	if(!(db.getName() == "SQLiteTests02.db"))
	{
		return false;
	}

	sql.removeDatabase("SQLiteTests02.db");
	// elimina la base de datos y el archivo .db
	db.deleteDatabase();

	if(!(sql.getListDatabases().length() == 0))
	{
		return false;
	}

	return true;
}

bool SQLiteTests::testRemoveNonExistentDatabaseReturnsFalse()
{
	SQLite sql;
	sql.createDatabase("SQLiteTests03.db");

	bool res = sql.removeDatabase("test04.db");

	if(res)
	{
		sql.getDatabase("SQLiteTests03.db").deleteDatabase();
		return false;
	}
		
	sql.getDatabase("SQLiteTests03.db").deleteDatabase();
	return true;
}

SQLiteTests::~SQLiteTests(void)
{
}
