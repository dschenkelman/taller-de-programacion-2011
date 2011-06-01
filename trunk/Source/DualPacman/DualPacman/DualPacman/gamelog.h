#include "database.h"
#include "query.h"

#pragma once

class gamelog
{
private:
	database* db;
	bool gamelog::newUserGameEntry(char* player, int points);
public:
	gamelog(char* uri);
	bool login(char* name, char* password);
	bool login(char* name);
	bool createPlayer(char* name, char* password);
	bool insertGame(char* player0, char* player1, int winner, int points0, int points1, int duration);
	query* gamelog::playersByPlayedTime();
	query* gamelog::playersByGamesPlayed();
	query* gamelog::playersByTotalPoints();
	query* gamelog::playersByWinnedCount();
	query* gamelog::playersComparison(char* player0, char* player1);
	query* getPlayers();
	~gamelog(void);
};
