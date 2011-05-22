#include "query.h"

#include "sqlite/sqlite3.h"

#include <iostream>
using namespace std;

query::query(sqlite3* db, char* sql)
{
	this->db = db;
	this->sql = sql;
	int retval = sqlite3_prepare_v2(db,sql,-1,&this->stmt,0);
	if(retval)
	{
		cout << "Selecting data from DB Failed" << endl;
		//return -1;
	}
}

int query::getValue(int colNr)
{
	return sqlite3_column_int(this->stmt, colNr);
}

int query::getPosition()
{
	return this->position;
}

int query::next()
{
	int res = sqlite3_step(this->stmt);
	if(res == SQLITE_DONE) return -1;
	else if(res == SQLITE_ROW) return 0;
	else return -2;
}

query::~query(void)
{
	sqlite3_finalize(this->stmt);
}
