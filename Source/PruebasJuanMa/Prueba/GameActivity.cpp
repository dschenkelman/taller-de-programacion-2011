#include "StdAfx.h"
#include "GameActivity.h"
#include "Activity.h"
#include "MenuActivity.h"

void GameActivity::onLoad(){
	
	// titulo y cabecera
	this->banner = new Image("images/dual.bmp");
	this->title = new RichTextView("pacman", RichTextView::NORMAL);
	this->title->setX(100); this->title->setY(50);

	// los agrego a la pantalla
	//this->add(this->banner, 0, 0);
	this->add(this->title);
	
}


Activity* GameActivity::notify(SDL_Event e){
	
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