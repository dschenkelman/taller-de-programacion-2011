#include "StdAfx.h"
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

query* DAO::getComparisonBetweenPlayers(std::string nameOne, std::string nameTwo)
{
	return glog->playersComparison((char*)nameOne.c_str(), (char*)nameTwo.c_str());
}

std::string DAO::getPassword(std::string name)
{
	//return glog->getPassword((char*)name.c_str());
	std::string ret = "lala";
	return ret;
}

void DAO::createPlayer(std::string name, std::string pass)
{
	glog->createPlayer((char*)name.c_str(), (char*)pass.c_str());
}

DAO::~DAO(void)
{
	delete this->glog;
}
