#include "List.h"
#include "Database.h"
#include <string>
#pragma once

class SQLite
{
private:
	List<Database> listDatabases;
public:
	SQLite(void);
	bool createDatabase(std::string uri);
	bool removeDatabase(std::string name);
	bool openDatabase(std::string uri);
	List<Database> getListDatabases();
	Database getDatabase(int index);
	Database getDatabase(std::string uri);
	~SQLite(void);
};