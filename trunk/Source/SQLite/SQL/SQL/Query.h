#include "sqlite/sqlite3.h"
#include <string>
#include "QueryResult.h"
#include "List.h"
#pragma once

class Query
{
private:
	sqlite3* db;
	std::string query;
	List<QueryResult> queryResult;
public:
	Query(sqlite3* db, std::string q);
	List<QueryResult> getQueryResults();
	void execute();
	~Query(void);
};
