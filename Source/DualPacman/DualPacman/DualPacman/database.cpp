#include "sqlite/sqlite3.h"
#include "query.h"

#include "database.h"
#include <iostream>
using namespace std;

database::database(char* uri)
{
	int res = sqlite3_open(uri,&this->db);
	if(res)
	{
		//cout << "Database connection failed" << endl;
		//return -1;
	}
	//cout << "Connection successful" << endl;
}

char* database::execute(char* sql)
{
	char* res;
	sqlite3_exec(this->db, sql, NULL, 0, &res);
	//cout << sql << endl;
	return res;
}

query database::getQuery(char* sql)
{
	return query(this->db,sql);
}

query* database::getQuery_v2(char* sql)
{
	query* q = new query(this->db,sql);
	return q;
	//return query(this->db,sql);
}

database::~database(void)
{
	sqlite3_close(this->db);
	this->db = NULL;
}
