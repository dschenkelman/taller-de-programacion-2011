#include "StdAfx.h"
#include "PresentationActivity.h"
#include "MenuActivity.h"
#include "Activity.h"


PresentationActivity::PresentationActivity(int width, int height):Activity(width, height){
}

PresentationActivity::PresentationActivity(Escenario escenario, int width, int height):Activity(escenario, width, height){
}

PresentationActivity::~PresentationActivity(){
}


void PresentationActivity::onLoad(){
	
	// cabecera
	this->banner = new ImageView("Images/title-pacman.bmp");
	this->banner->setX(0); this->banner->setY(0);

	// insertcoin
	this->insertCoin = new RichTextView("Insert coin", RichTextView::NORMAL);
	this->insertCoin->setX(40); this->insertCoin->setY(200);

	// menu con flecha
	this->arrowMenu = new OptionArrowMenuView();
	this->arrowMenu->setX(50); this->arrowMenu->setY(250); 
	this->arrowMenu->addOption("hit enter");

	// los agrego a la pantalla
	this->add(this->banner);
	this->add(this->insertCoin);
	this->add(this->arrowMenu);

}

Activity* PresentationActivity::notify(SDL_Event e){

	Activity* nextActivity = NULL;

	switch(e.type){
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym){
				case SDLK_RETURN:
					nextActivity = new MenuActivity(this->getWidth(), this->getHeight());
					break;
			}
			break;
	}

	return nextActivity;

}