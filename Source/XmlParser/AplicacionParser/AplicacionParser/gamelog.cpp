#include "stdafx.h"
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
	string sql("SELECT Id FROM Players WHERE Name=");
	sql += string(name);
	sql += string(" AND Password=");
	sql += string(password);
	query q = db->getQuery((char*)sql.c_str());
	
	unsigned int id = q.getInt(0);
	if (id > 0) return true;
	return false;
}

bool gamelog::login(char* name) {
	string sql("SELECT Id FROM Players WHERE Name=");
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

bool gamelog::insertGame(char* player0, char* player1, int points0, int points1, int duration) {
	int winner;
	if (points0>points1) winner=0;
	else winner=1;
	return gamelog::insertGame(player0,player1,winner,points0,points1,duration);
}
query* gamelog::getPlayers()
{
       return this->db->getQuery_v2("SELECT * FROM Players");
}

query* gamelog::playersByPlayedTime()
{
	return this->db->getQuery_v2("SELECT p.Name,sum(distinct Duration) AS TotalPlayed FROM Games g INNER JOIN UserGame ug ON g.Id=ug.GameId INNER JOIN Players p ON p.Id=ug.PlayerId GROUP BY PlayerId;");
}

query* gamelog::playersByGamesPlayed()
{
	return this->db->getQuery_v2("select count(distinct ug.gameid) as GamesPlayed,p.name from usergame ug inner join players p on p.id=ug.playerid group by ug.playerid;");
}

query* gamelog::playersByTotalPoints()
{
	return this->db->getQuery_v2("select sum(distinct ug.points) as TotalPoints,p.name from usergame ug inner join players p on p.id=ug.playerid group by ug.playerid;");
}

query* gamelog::playersByWinnedCount()
{
	return this->db->getQuery_v2("select count(g.winnerid)as WinnedCount,p.name from games g inner join players p on p.id=g.winnerid group by g.winnerid;");
}

query* gamelog::playersComparison(char* player0, char* player1)
// select p0.name as Player0,p1.name as Player1,ug0.points as Points0,ug1.points as Points1,pw.name as Winner,g.duration from games g inner join usergame ug0 on p0.name='ale' and ug0.gameid=g.id inner join usergame ug1 on p1.name='juan' and ug1.gameid=g.id inner join players p0 on p0.id=ug0.playerid inner join players p1 on p1.id=ug1.playerid inner join players pw on pw.id=g.winnerid order by g.id;
{
	string sql("select p0.name as Player0,p1.name as Player1,ug0.points as Points0,ug1.points as Points1,pw.name as Winner,g.duration from games g inner join usergame ug0 on p0.name='");
	sql += string(player0);
	sql += string("' and ug0.gameid=g.id inner join usergame ug1 on p1.name='");
	sql += string(player1);
	sql += string("' and ug1.gameid=g.id inner join players p0 on p0.id=ug0.playerid inner join players p1 on p1.id=ug1.playerid inner join players pw on pw.id=g.winnerid order by g.id;");
	return this->db->getQuery_v2((char*)sql.c_str());
}

gamelog::~gamelog(void)
{
	delete(db);
}
