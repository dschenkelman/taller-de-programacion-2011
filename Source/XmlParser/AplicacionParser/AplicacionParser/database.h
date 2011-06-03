#include "sqlite/sqlite3.h"
#include "query.h"

#pragma once

class database
{
private:
	sqlite3* db;
public:
	database(char* uri);
	char* execute(char* sql);
	query getQuery(char* sql);
	query* database::getQuery_v2(char* sql);
	~database(void);
};
