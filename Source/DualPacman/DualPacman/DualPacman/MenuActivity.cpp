#include "StdAfx.h"
#include "MenuActivity.h"
#include "Activity.h"
#include "GameActivity.h"
#include "StatsActivity.h"
#include "CreatePlayerActivity.h"


MenuActivity::MenuActivity(int width, int height):Activity(width, height){
}


void MenuActivity::onLoad(){
	
	// cabecera
	this->banner = new ImageView("Images/dual.bmp");
	this->banner->setX(5); this->banner->setY(5);
	this->banner->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// titulo
	this->title = new RichTextView("pacman", RichTextView::NORMAL);
	this->title->setY(50);
	this->title->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);
	
	// menu con flecha
	this->arrowMenu = new OptionArrowMenuView();
	this->arrowMenu->setX(50); this->arrowMenu->setY(200); 
	this->arrowMenu->addOption("new game");
	this->arrowMenu->addOption("create player");
	this->arrowMenu->addOption("stats");
	this->arrowMenu->addOption("quit");

	// los agrego a la pantalla
	this->add(this->banner);
	this->add(this->title);
	this->add(this->arrowMenu);

}

Activity* MenuActivity::notify(SDL_Event e){

	Activity* nextActivity = NULL;

	switch(e.type){
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym){
				case SDLK_RETURN:
					if(this->arrowMenu->getSelectedOption() == "new game")
						nextActivity = new GameActivity(this->getWidth(), this->getHeight());

					if(this->arrowMenu->getSelectedOption() == "create player")
						nextActivity = new CreatePlayerActivity(this->getWidth(), this->getHeight());

					if(this->arrowMenu->getSelectedOption() == "stats")
						nextActivity = new StatsActivity(this->getWidth(), this->getHeight());

					if(this->arrowMenu->getSelectedOption() == "quit")
						SDL_Quit();

					break;
				default:
					this->arrowMenu->notify(e);
					break;
			}
			break;
	}

	return nextActivity;

}