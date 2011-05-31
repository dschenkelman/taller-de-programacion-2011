#include "DAO.h"

DAO::DAO(char* uri)
{
	this->glog = new gamelog(uri);
}

query* DAO::getRankingByPoints()
{
	/*List<std::string> usersList;
	usersList.add("Juanma 1000");
	usersList.add("Gonzo 8000");
	return usersList;*/
	
	return glog->playersByTotalPoints();
}

query* DAO::getRankingByTime()
{
	/*List<std::string> usersList;
	usersList.add("Juanma 13 hs");
	usersList.add("Gonzo 10 hs");
	return usersList;*/

	return glog->playersByPlayedTime();
}

query* DAO::getRankingByGamesPlayed()
{
	/*List<std::string> usersList;
	usersList.add("Gonzo 15");
	usersList.add("Juanma 13");
	return usersList;*/

	return glog->playersByGamesPlayed();
}

query* DAO::getRankingByWins()
{
	/*List<std::string> usersList;
	usersList.add("Gonzo 9");
	usersList.add("Juanma 8");
	return usersList;*/

	return glog->playersByWinnedCount();
}

DAO::~DAO(void)
{
	delete this->glog;
}
