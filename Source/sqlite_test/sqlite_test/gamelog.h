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
	~gamelog(void);
};
