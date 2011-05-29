#include "DAO.h"

DAO::DAO(void)
{
}

List<std::string> DAO::getRankingByPoints()
{
	List<std::string> usersList;
	usersList.add("Juanma 1000");
	usersList.add("Gonzo 8000");
	return usersList;
}

List<std::string> DAO::getRankingByTime()
{
	List<std::string> usersList;
	usersList.add("Juanma 13 hs");
	usersList.add("Gonzo 10 hs");
	return usersList;
}

List<std::string> DAO::getRankingByGamesPlayed()
{
	List<std::string> usersList;
	usersList.add("Gonzo 15");
	usersList.add("Juanma 13");
	return usersList;
}

List<std::string> DAO::getRankingByWins()
{
	List<std::string> usersList;
	usersList.add("Gonzo 9");
	usersList.add("Juanma 8");
	return usersList;
}

DAO::~DAO(void)
{
}
