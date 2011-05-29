#include "StdAfx.h"
#include "StatsActivity.h"
#include "MenuActivity.h"
#include "Activity.h"


StatsActivity::StatsActivity(int width, int height):Activity(width, height){
}


void StatsActivity::onLoad(){
	
	// cabecera
	this->banner = new ImageView("Images/dual.bmp");
	this->banner->setX(5); this->banner->setY(5);

	// titulo
	this->title = new RichTextView("Stats", RichTextView::NORMAL);
	this->title->setX(100); this->title->setY(50);
	
	// menu con flecha
	this->arrowMenu = new OptionArrowMenuView();
	this->arrowMenu->setX(50); this->arrowMenu->setY(200); 
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

					break;
			}
			break;
	}

	return nextActivity;

}