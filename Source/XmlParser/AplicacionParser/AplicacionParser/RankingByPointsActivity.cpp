#include "StdAfx.h"
#include "RankingByPointsActivity.h"
#include "StatsActivity.h"
#include "Activity.h"
#include "DAO.h"

RankingByPointsActivity::RankingByPointsActivity(int width, int height):Activity(width, height){
}

void RankingByPointsActivity::onLoad()
{
	// cabecera
	this->banner = new ImageView("Images/dual.bmp");
	this->banner->setX(5); this->banner->setY(5);
	this->banner->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// titulo
	this->title = new RichTextView("Ranking by points", RichTextView::NORMAL);
	this->title->setX(100); this->title->setY(50);
	this->title->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// datos
	List<std::string> ranking = DAO().getRankingByPoints();
	int userY = 200;
	for(int i = 0; i < ranking.length(); i++)
	{
		std::string str = ranking.at(i);
		RichTextView* rtv = new RichTextView(str, RichTextView::NORMAL);
		rtv->setX(100); rtv->setY(userY);
		this->add(rtv);
		userY += 50;
	}

	// menu con flecha
	this->arrowMenu = new OptionArrowMenuView();
	this->arrowMenu->setX(50); this->arrowMenu->setY(this->getHeight() - 200); 
	this->arrowMenu->addOption("return to menu");

	// los agrego a la pantalla
	this->add(this->banner);
	this->add(this->title);
	this->add(this->arrowMenu);
}

Activity* RankingByPointsActivity::notify(SDL_Event e){

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

RankingByPointsActivity::~RankingByPointsActivity()
{
	delete this->banner;
	delete this->title;
	delete this->arrowMenu;
}
