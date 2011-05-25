#include "List.h"
#include "sqlite/sqlite3.h"
#include <string>
#include "Query.h"
#pragma once

using namespace std;

class Database
{
private:
	sqlite3* db;
	bool error;
	std::string name;
	List<std::string> listTables;
public:
	Database(std::string name);
	Database(void);
	bool hasError();
	std::string getName();
	void deleteDatabase();
	void createTable(std::string name, List<std::string> args);
	void removeTable(std::string name);
	void insertData(std::string tn, List<std::string> v);
	void updateData(std::string tn, List<std::string> v);
	List<QueryResult> executeQuery(Query q);
	List<QueryResult> executeQuery(std::string q);
	List<std::string> getTables();
	~Database(void);
};
