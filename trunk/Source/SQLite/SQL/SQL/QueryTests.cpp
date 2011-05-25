#include "QueryTests.h"
#include "List.h"
#include "QueryResult.h"
#include "sqlite/sqlite3.h"
#include <cstring>
#include <iostream>

QueryTests::QueryTests(void)
{
}

void QueryTests::printLeaks(int leaks)
{
	std::cout << "Bonus Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

void QueryTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

void QueryTests::run()
{
	printResult("testExecuteQueryWithoutResults", testExecuteQueryWithoutResults());
	printResult("testExecuteQueryWithResults", testExecuteQueryWithResults());

    int leaks = _CrtDumpMemoryLeaks();
    printLeaks(leaks);
}

bool QueryTests::testExecuteQueryWithoutResults()
{
	sqlite3* database;
	int openRes = sqlite3_open("QueryTests01.db", &database);

	std::string queryString = "CREATE TABLE PERSONAS (NOMBRE VARCHAR(20), EDAD INT)";
	std::string queryString2 = "INSERT INTO PERSONAS VALUES('Roman', '32')";

	Query query(database, queryString);
	Query query2(database, queryString2);

	query.execute();
	query2.execute();

	std::string qs = "select * from PERSONAS";

	char** result;
	int rows;
	int cols;
	int tableRes = sqlite3_get_table(database, qs.c_str(), &result, &rows, &cols, NULL);

	if(!tableRes == SQLITE_OK)
	{
		sqlite3_close(database);
		remove("QueryTests01.db");
		return false;
	}

	if(rows != 1)
	{
		sqlite3_close(database);
		remove("QueryTests01.db");
		return false;
	}

	if(cols != 2)
	{
		sqlite3_close(database);
		remove("QueryTests01.db");
		return false;
	}

	if (strcmp(result[0], "NOMBRE") != 0)
	{
		sqlite3_close(database);
		remove("QueryTests01.db");
		return false;
	}

	if (strcmp(result[1], "EDAD") != 0)
	{
		sqlite3_close(database);
		remove("QueryTests01.db");
		return false;
	}

	if (strcmp(result[2], "Roman") != 0)
	{
		sqlite3_close(database);
		remove("QueryTests01.db");
		return false;
	}

	if (strcmp(result[3], "32") != 0)
	{
		sqlite3_close(database);
		remove("QueryTests01.db");
		return false;
	}

	sqlite3_close(database);
	remove("QueryTests01.db");

	return true;
}

bool QueryTests::testExecuteQueryWithResults()
{
	sqlite3* database;
	int openRes = sqlite3_open("QueryTests02.db", &database);

	std::string queryString = "CREATE TABLE PERSONAS (NOMBRE VARCHAR(20), EDAD INT)";
	std::string queryString2 = "INSERT INTO PERSONAS VALUES('Roman', '32')";
	std::string queryString3 = "INSERT INTO PERSONAS VALUES('Ana', '23')";

	Query query(database, queryString);
	Query query2(database, queryString2);
	Query query3(database, queryString3);

	query.execute();
	query2.execute();
	query3.execute();

	std::string qs = "select * from PERSONAS";

	Query query4(database, qs);
	query4.execute();
	List<QueryResult> queryResults = query4.getQueryResults();

	for(int i = 0; i < queryResults.length(); i++)
	{
		bool successCondition1 = (queryResults.at(i).getValue("NOMBRE") == "Roman")
			&& (queryResults.at(i).getValue("EDAD") == "32");
		bool successCondition2 = (queryResults.at(i).getValue("NOMBRE") == "Ana")
			&& (queryResults.at(i).getValue("EDAD") == "23");

		if(!(successCondition1 || successCondition2))
		{
			sqlite3_close(database);
			remove("QueryTests02.db");
			return false;
		}
	}

	sqlite3_close(database);
	remove("QueryTests02.db");
	return true;
}

QueryTests::~QueryTests(void)
{
}
