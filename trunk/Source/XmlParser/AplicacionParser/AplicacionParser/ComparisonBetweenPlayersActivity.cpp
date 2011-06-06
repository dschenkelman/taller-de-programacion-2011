#include "StdAfx.h"
#include "ComparisonBetweenPlayersActivity.h"
#include "DAO.h"

ComparisonBetweenPlayersActivity::ComparisonBetweenPlayersActivity(int width, int height, 
		std::string playerOne, std::string playerTwo):Activity(width, height)
{
	this->playerOne = playerOne;
	this->playerTwo = playerTwo;
}

void ComparisonBetweenPlayersActivity::onLoad()
{
	// cabecera
	this->banner = new ImageView("Images/dual.bmp");
	this->banner->setX(5); this->banner->setY(5);
	this->banner->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// titulo
	this->title = new RichTextView("Comparison between players", RichTextView::NORMAL);
	this->title->setY(50);
	this->title->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	//datos
	DAO d("gamelog.sql");
	query* players = d.getComparisonBetweenPlayers(this->playerOne, this->playerTwo);

	this->arrowMenu = new OptionArrowMenuView();
	this->arrowMenu->addOption("return to stats");

}

Activity* ComparisonBetweenPlayersActivity::notify(SDL_Event e)
{
	return new Activity(530, 504);
}

ComparisonBetweenPlayersActivity::~ComparisonBetweenPlayersActivity(void)
{
}
