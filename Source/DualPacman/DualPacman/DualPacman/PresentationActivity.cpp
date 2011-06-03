#include "StdAfx.h"
#include "PresentationActivity.h"
#include "MenuActivity.h"
#include "Activity.h"


PresentationActivity::PresentationActivity(int width, int height):Activity(width, height){
}

PresentationActivity::PresentationActivity(ParameterHolder* params, int width, int height):Activity(params, width, height){
}

PresentationActivity::~PresentationActivity(){
}


void PresentationActivity::onLoad(){

	// cabecera
	this->banner = new ImageView("Images/title-pacman.bmp");
	this->banner->setX(0); this->banner->setY(0);

	this->prueba = "hola";

	// insertcoin
	this->insertCoin = new RichTextView(this->prueba, RichTextView::NORMAL);
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
				default:
					this->prueba = this->prueba + "s";
					RichTextView* f = new RichTextView(this->prueba, RichTextView::NORMAL);
					f->setX(40); f->setY(200);
					this->updateViewFromView(this->insertCoin, f);
			}
			break;
	}

	return nextActivity;

}