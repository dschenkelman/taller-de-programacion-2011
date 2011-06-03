#include "List.h"
#include <string>
#include "query.h"
#include "gamelog.h"
#pragma once

class DAO
{
private:
	gamelog* glog;
public:
	DAO(char* uri);
	query* getRankingByPoints();
	query* getRankingByTime();
	query* getRankingByGamesPlayed();
	query* getRankingByWins();
	query* getPlayers();
	void createPlayer(std::string name, std::string pass);
	~DAO(void);
};
