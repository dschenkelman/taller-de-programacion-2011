#include "StdAfx.h"
#include "StatsActivity.h"
#include "Activity.h"
#include "DAO.h"
#include "RankingByWinsActivity.h"
#include <sstream>

RankingByWinsActivity::RankingByWinsActivity(int width, int height):Activity(width, height)
{
}

void RankingByWinsActivity::onLoad()
{
		// cabecera
	this->banner = new ImageView("Images/dual.bmp");
	this->banner->setX(5); this->banner->setY(5);
	this->banner->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// titulo
	this->title = new RichTextView("Ranking by wins", RichTextView::NORMAL);
	this->title->setX(100); this->title->setY(50);
	this->title->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// datos
	DAO dao("gamelog.sql");
	query* query = dao.getRankingByWins();
	int userY = 200;

	while(!query->next())
	{
		std::string name = query->getChars(1);
		std::stringstream out;
		out << query->getInt(0);
		std::string wins = out.str();
		
		RichTextView* rtvName = new RichTextView(name, RichTextView::NORMAL);
		rtvName->setX(100); rtvName->setY(userY);
		
		RichTextView* rtvWins = new RichTextView(wins, RichTextView::NORMAL);
		rtvWins->setX(this->getWidth() - 120); rtvWins->setY(userY);

		this->add(rtvName); this->add(rtvWins);

		userY += 20;
	}

	delete query;

	// menu con flecha
	this->arrowMenu = new OptionArrowMenuView();
	this->arrowMenu->setX(50); this->arrowMenu->setY(this->getHeight() - 50); 
	this->arrowMenu->addOption("return to menu");

	// los agrego a la pantalla
	this->add(this->banner);
	this->add(this->title);
	this->add(this->arrowMenu);
}

Activity* RankingByWinsActivity::notify(SDL_Event e){

	Activity* nextActivity = NULL;

	switch(e.type){
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym){
				case SDLK_RETURN:
					if(this->arrowMenu->getSelectedOption() == "return to menu")
						nextActivity = new StatsActivity(this->getWidth(), this->getHeight());
					
					break;
			}
			break;
	}

	return nextActivity;
}