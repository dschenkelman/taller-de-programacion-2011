#include "Gamelog.h"
#include "database.h"
#include "query.h"

#include <iostream>
#include <string>
using namespace std;

gamelog::gamelog(char* uri)
{
	db = new database(uri);
	char* debugmsg;
	debugmsg = db->execute("CREATE TABLE IF NOT EXISTS Players (Id INTEGER PRIMARY KEY, Name TEXT, Password TEXT)");
	if (debugmsg) cout << debugmsg << endl;
	debugmsg = db->execute("CREATE TABLE IF NOT EXISTS Games (Id INTEGER PRIMARY KEY, WinnerId INTEGER, Duration INTEGER, FOREIGN KEY(WinnerId) REFERENCES Players(PlayerId))");
	if (debugmsg) cout << debugmsg << endl;
	debugmsg = db->execute("CREATE TABLE IF NOT EXISTS UserGame (GameId INTEGER, PlayerId INTEGER, Points INTEGER, FOREIGN KEY(GameId) REFERENCES Games(Id), FOREIGN KEY(PlayerId) REFERENCES Players(PlayerId))");
	if (debugmsg) cout << debugmsg << endl;
}

bool gamelog::login(char* name, char* password) {
	string sql("SELECT Id FROM Players WHERE?AND Name=");
	sql += string(name);
	sql += string("WHERE?AND Password=");
	sql += string(password);
	query q = db->getQuery((char*)sql.c_str());
	
	unsigned int id = q.getInt(0);
	if (id > 0) return true;
	return false;
}

bool gamelog::login(char* name) {
	string sql("SELECT Id FROM Players WHERE?AND Name=");
	sql += string(name);
	query q = db->getQuery((char*)sql.c_str());
	
	unsigned int id = q.getInt(0);
	if (id > 0) return true;
	return false;
}

bool gamelog::createPlayer(char* name, char* password) {
	if (login(name)) return false;
	string sql("INSERT INTO Players(Name,Password) VALUES (\"");
	sql += string(name);
	sql += string("\", \"");
	sql += string(password);
	sql += string("\")");
	char* res = db->execute((char*)sql.c_str());
	if (res) cout << res << endl;
	return !(bool)res;
}

bool gamelog::insertGame(char* player0, char* player1, int winner, int points0, int points1, int duration) {
	string sql("INSERT INTO Games(WinnerId,Duration) SELECT Id,'");
	char buffer[50];
	sql += string(itoa(duration,buffer,10));
	sql += string("' FROM Players WHERE Name='");
	if (winner==0) sql += string(player0);
	if (winner==1) { sql += string(player1); } else return false;
	sql += string("'");
	char* res = db->execute((char*)sql.c_str());
	if (res) cout << res << endl;
	return !(bool)res;
}

gamelog::~gamelog(void)
{
	delete(db);
}
