#include "StdAfx.h"
#include "StatsActivity.h"
#include "MenuActivity.h"
#include "Activity.h"
#include "RankingByPointsActivity.h"
#include "RankingByGamesPlayedActivity.h"
#include "RankingByWinsActivity.h"
#include "RankingByTimeActivity.h"


StatsActivity::StatsActivity(int width, int height):Activity(width, height){
}


void StatsActivity::onLoad(){
	
	// cabecera
	this->banner = new ImageView("Images/dual.bmp");
	this->banner->setX(5); this->banner->setY(5);
	this->banner->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// titulo
	this->title = new RichTextView("Stats", RichTextView::NORMAL);
	this->title->setX(100); this->title->setY(50);
	this->title->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// menu con flecha
	this->arrowMenu = new OptionArrowMenuView();
	this->arrowMenu->setX(50); this->arrowMenu->setY(200); 
	this->arrowMenu->addOption("ranking by points");
	this->arrowMenu->addOption("ranking by games played");
	this->arrowMenu->addOption("ranking by wins");
	this->arrowMenu->addOption("ranking by time");
	this->arrowMenu->addOption("comparison between players");
	this->arrowMenu->addOption("return to menu");

	// los agrego a la pantalla
	this->add(this->banner);
	this->add(this->title);
	this->add(this->arrowMenu);

}

Activity* StatsActivity::notify(SDL_Event e){

	Activity* nextActivity = NULL;

	switch(e.type){
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym){
				case SDLK_RETURN:
					if(this->arrowMenu->getSelectedOption() == "return to menu")
						nextActivity = new MenuActivity(this->getWidth(), this->getHeight());

					if(this->arrowMenu->getSelectedOption() == "ranking by points")
						nextActivity = new RankingByPointsActivity(this->getWidth(), this->getHeight());
					
					if(this->arrowMenu->getSelectedOption() == "ranking by games played")
						nextActivity = new RankingByGamesPlayedActivity(this->getWidth(), this->getHeight());
					
					if(this->arrowMenu->getSelectedOption() == "ranking by wins")
						nextActivity = new RankingByWinsActivity(this->getWidth(), this->getHeight());

					if(this->arrowMenu->getSelectedOption() == "ranking by time")
						nextActivity = new RankingByTimeActivity(this->getWidth(), this->getHeight());

					/*if(this->arrowMenu->getSelectedOption() == "comparison between players")
						nextActivity = new RankingByPointsActivity(this->getWidth(), this->getHeight());*/

					break;
				default:
					this->arrowMenu->notify(e);
					break;
			}
			break;
	}

	return nextActivity;

}

StatsActivity::~StatsActivity()
{
	/*delete this->arrowMenu;
	delete this->title;
	delete this->banner;*/
}