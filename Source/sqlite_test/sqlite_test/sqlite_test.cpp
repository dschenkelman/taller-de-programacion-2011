#include "sqlite_test.h"
#include "sqlite/sqlite3.h"
#include <iostream>
using namespace std;

int main() {
	cout << "hello world!" << endl;
	sqlite3* testdb;
	char* testdb_err;
	sqlite3_open("testdb.db", &testdb);
	sqlite3_exec(testdb, "create table 'testtable' (id integer);", NULL, 0, &testdb_err);
	sqlite3_close(testdb);
	return 0;
}

sqlite_test::sqlite_test(void)
{
}

sqlite_test::~sqlite_test(void)
{
}
