#include "Database.h"
#include "QueryResult.h"

Database::Database(void)
{
}

Database::Database(std::string uri)
{
	this->error = false;
	this->name = uri;
	int res = sqlite3_open(this->name.c_str(), &this->db);

	if (res)
	{
		this->error = true;
	}
}

void Database::deleteDatabase()
{
	std::string query = "DROP DATABASE IF EXISTS " + this->name;
	
	Query q(this->db, query);
	q.execute();
	sqlite3_close(this->db);
	remove(this->name.c_str());
}

void Database::createTable(std::string name, List<std::string> args)
{
	std::string query = "CREATE TABLE " + name + "(";
	
	for(int i = 0; i < args.length(); i++)
	{
		query += " " + args.at(i) + ",";
	}

	this->listTables.add(name);

	query.erase(query.size()-1, 1);
	query+= ")";

	Query q(this->db, query);
	q.execute();
}

void Database::removeTable(std::string tableName)
{
	std::string query = "DROP TABLE IF EXISTS " + tableName;

	if(this->listTables.contains(tableName))
	{
		for(int i = 0; i < this->listTables.length(); i++)
		{
			if(this->listTables.at(i) == tableName)
			{
				this->listTables.removeAt(i);
			}
		}
	}

	Query q(this->db, query);
	q.execute();
}

void Database::insertData(std::string tableName, List<std::string> values)
{
	std::string query = "INSERT INTO " + tableName + " VALUES (";

	for(int i = 0; i < values.length(); i++)
	{
		query += values.at(i) + ",";
	}

	query.erase(query.size()-1, 1);
	query += ")";

	Query q(this->db, query);
	q.execute();
}

void Database::updateData(std::string tableName, List<std::string> values)
{
	std::string query = "UPDATE " + tableName + " SET";

	for(int i = 0; i < values.length(); i++)
	{
		query += " " + values.at(i) + ",";
	}

	query.erase(query.size()-1, 1);

	Query q(this->db, query);
	q.execute();
}

List<QueryResult> Database::executeQuery(Query q)
{
	q.execute();
	return q.getQueryResults();
}

List<QueryResult> Database::executeQuery(std::string q)
{
	Query query(this->db, q);
	query.execute();
	return query.getQueryResults();
}

std::string Database::getName()
{
	return this->name;
}

List<std::string> Database::getTables()
{
	return this->listTables;
}

bool Database::hasError()
{
	return this->error;
}

Database::~Database(void)
{
	//sqlite3_close(this->db);
	this->db = NULL;
}
