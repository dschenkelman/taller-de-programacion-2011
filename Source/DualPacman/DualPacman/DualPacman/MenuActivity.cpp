#include "StdAfx.h"
#include "MenuActivity.h"
#include "Activity.h"
#include "GameActivity.h"

void MenuActivity::onLoad(){
	
	// titulo y cabecera
	//this->banner = new Image("images/title-pacman.bmp");
	this->title = new RichTextView("pacman", RichTextView::NORMAL);
	this->title->setX(100); this->title->setY(50);
	
	// menu con flecha
	this->arrowMenu = new OptionArrowMenuView();
	this->arrowMenu->setX(50); this->arrowMenu->setY(200); 
	this->arrowMenu->addOption("start");
	this->arrowMenu->addOption("quit");

	// los agrego a la pantalla
	//this->add(this->banner, 0, 0);
	this->add(this->title);
	this->add(this->arrowMenu);

}

Activity* MenuActivity::notify(SDL_Event e){

	Activity* nextActivity = NULL;

	switch(e.type){
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym){
				case SDLK_RETURN:
					if(this->arrowMenu->getSelectedOption() == "start")
						nextActivity = new GameActivity();
					
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