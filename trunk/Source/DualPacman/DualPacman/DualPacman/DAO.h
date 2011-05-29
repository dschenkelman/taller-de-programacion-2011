#include "List.h"
#include <string>
#pragma once

class DAO
{
public:
	DAO(void);
	List<std::string> getRankingByPoints();
	List<std::string> getRankingByTime();
	List<std::string> getRankingByGamesPlayed();
	List<std::string> getRankingByWins();
public:
	~DAO(void);
};
