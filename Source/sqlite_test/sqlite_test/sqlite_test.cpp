#include "database.h"
#include "query.h"
#include "sqlite_test.h"
#include <iostream>
using namespace std;

int main() {
	cout << "hello world!" << endl;
	remove("test.sql");
	database db("test.sql");
	char* res;
	res = db.execute("CREATE TABLE IF NOT EXISTS table0 (col0 INTEGER, col1 INTEGER)");
	if (res) cout << res << endl;
	res = db.execute("INSERT INTO table0 VALUES (123, 456)");
	if (res) cout << res << endl;
	query q = db.getQuery("SELECT * FROM table0");
	int n0 = q.getValue(1);
	cout << n0 << endl;
	char c = getchar();
	return 0;
}

sqlite_test::sqlite_test(void)
{
}

sqlite_test::~sqlite_test(void)
{
}
