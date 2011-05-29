#include "database.h"
#include "query.h"
#include "sqlite_test.h"
#include "gamelog.h"
#include <iostream>
using namespace std;

//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main() {
	cout << "hello world!" << endl;
	remove("test.sql");
	database db("test.sql");
	char* res;
	res = db.execute("CREATE TABLE IF NOT EXISTS table0 (col0 INTEGER, col1 TEXT)");
	if (res) cout << res << endl;
	res = db.execute("INSERT INTO table0 VALUES (123, 'texto!')");
	if (res) cout << res << endl;
	query q = db.getQuery("SELECT * FROM table0");
	q.next();
	int n;
	n = q.getInt(0);
	cout << n << endl;
	char* t;
	t = q.getChars(1);
	cout << t << endl;
	
	remove("gamelog.sql");
	gamelog glog = gamelog("gamelog.sql");
	glog.createPlayer("ale","alepass");
	glog.createPlayer("ela","elapass");
	glog.createPlayer("juan","juanpass");
	glog.insertGame("ale","ela",0,10,20,60);
	glog.insertGame("ela","ale",0,30,40,50);
	glog.insertGame("ale","juan",1,15,25,70);

	query* stats = glog.playersByPlayedTime();
	while(!stats->next()) {
		cout << "Jugador: " << stats->getChars(0) << " Puntos: " << stats->getInt(1) << endl;
	}

	//dump memory leaks to VS Output Window
	int leaks = _CrtDumpMemoryLeaks();
	cout << "Memory leaks: " << leaks << endl;

	getchar();
	return 0;
}

sqlite_test::sqlite_test(void)
{
}

sqlite_test::~sqlite_test(void)
{
}
