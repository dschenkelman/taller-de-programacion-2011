#include "StdAfx.h"
#include "PresentationActivity.h"
#include "MenuActivity.h"
#include "Activity.h"

void PresentationActivity::onLoad(){
	
	// cabecera
	this->banner = new ImageView("Images/title-pacman.bmp");
	this->banner->setX(5); this->banner->setY(5);

	// menu con flecha
	this->arrowMenu = new OptionArrowMenuView();
	this->arrowMenu->setX(50); this->arrowMenu->setY(200); 
	this->arrowMenu->addOption("hit enter");

	// los agrego a la pantalla
	this->add(this->banner);
	this->add(this->arrowMenu);

}

Activity* PresentationActivity::notify(SDL_Event e){

	Activity* nextActivity = NULL;

	switch(e.type){
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym){
				case SDLK_RETURN:
					nextActivity = new MenuActivity();
					break;
			}
			break;
	}

	return nextActivity;

}