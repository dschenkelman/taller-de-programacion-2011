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

bool gamelog::newUserGameEntry(char* player, int points) {
	string sql("INSERT INTO UserGame(GameId,Points) SELECT Id,");
	char buffer[50];
	sql += string(itoa(points,buffer,10));
	sql += string(" FROM Games ORDER BY Id DESC LIMIT 0,1;");
	char* res = db->execute((char*)sql.c_str());
	if (res) cout << res << endl;
	sql = string("UPDATE UserGame SET PlayerId=(SELECT Id FROM Players WHERE Name='");
	sql += string(player);
	sql += string("') WHERE GameId=(select id from games order by id desc limit 1) AND playerid is NULL;");
	res = db->execute((char*)sql.c_str());
	if (res) cout << res << endl;
	return false; // TODO
}

bool gamelog::insertGame(char* player0, char* player1, int winner, int points0, int points1, int duration) {
	string sql("BEGIN IMMEDIATE; INSERT INTO Games(WinnerId,Duration) SELECT Id,'");
	char buffer[50];
	sql += string(itoa(duration,buffer,10));
	sql += string("' FROM Players WHERE Name='");
	if (winner==0) sql += string(player0);
	else if (winner==1) { sql += string(player1); } else return false;
	sql += string("'");
	char* res = db->execute((char*)sql.c_str());
	if (res) cout << res << endl;

	this->newUserGameEntry(player0,points0);
	this->newUserGameEntry(player1,points1);
	db->execute("COMMIT;");
	return false; // TODO
}

query gamelog::playersByPlayedTime()
{
	string sql("SELECT PlayerId,sum(distinct Duration) AS TotalPlayed FROM Games g INNER JOIN UserGame ug ON g.Id=ug.GameId GROUP BY PlayerId;");
	query q = this->db->getQuery((char*)sql.c_str());
	return q;
}

query gamelog::playersByGamesPlayed()
{
	string sql("select count(distinct ug.gameid) as GamesPlayed,p.name from usergame ug inner join players p on p.id=ug.playerid group by ug.playerid;");
	query q = this->db->getQuery((char*)sql.c_str());
	return q;
}

gamelog::~gamelog(void)
{
	delete(db);
}
