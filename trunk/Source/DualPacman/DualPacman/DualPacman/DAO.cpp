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

void DAO::createPlayer(std::string name, std::string pass)
{
	glog->createPlayer((char*)name.c_str(), (char*)pass.c_str());
}

DAO::~DAO(void)
{
	delete this->glog;
}
