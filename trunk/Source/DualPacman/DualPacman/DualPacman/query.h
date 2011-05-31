#include "sqlite/sqlite3.h"
#pragma once

class query
{
private:
	char* sql;
	sqlite3* db;
	sqlite3_stmt* stmt;
	int position;
public:
	query(sqlite3* db, char* sql);
	int getInt(int colNr);
	char* getChars(int colNr);
	int getPosition();
	int next();
public:
	~query(void);
};
