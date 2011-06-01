#include "DAO.h"

DAO::DAO(char* uri)
{
	this->glog = new gamelog(uri);
}

query* DAO::getRankingByPoints()
{
	return glog->playersByTotalPoints();
}

query* DAO::getRankingByTime()
{
	return glog->playersByPlayedTime();
}

query* DAO::getRankingByGamesPlayed()
{
	return glog->playersByGamesPlayed();
}

query* DAO::getRankingByWins()
{
	return glog->playersByWinnedCount();
}

query* DAO::getPlayers()
{
	return glog->getPlayers();
}

DAO::~DAO(void)
{
	delete this->glog;
}
