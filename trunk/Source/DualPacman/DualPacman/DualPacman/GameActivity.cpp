#include "StdAfx.h"
#include "GameActivity.h"
#include "Activity.h"
#include "MenuActivity.h"
#include "ScreenManager.h"

void GameActivity::onLoad(){
	
	// titulo y cabecera
	this->banner = new Image("images/dual.bmp");
	this->title = new RichTextView("puntaje", RichTextView::NORMAL);
	this->title->setX(100); this->title->setY(0);


	this->period = 1000.0 / 60;
	this->screenManager = new ScreenManager(this, "Images/fondo.bmp");
	
	// los agrego a la pantalla
	//this->add(this->banner, 0, 0);
	this->add(this->title);
	
}


void GameActivity::update(){
	screenManager->updateScreen();
}

Activity* GameActivity::notify(SDL_Event e){
	
	Activity* nextActivity = NULL;

	switch(e.type){
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym){
				case SDLK_RETURN:
					nextActivity = new MenuActivity();
					break;
				default:
					screenManager->handleKeyStroke();
					
			}
			break;
	}

	screenManager->updateScreen();

	return nextActivity;
}