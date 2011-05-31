#include "StdAfx.h"
#include "GameActivity.h"
#include "Activity.h"
#include "MenuActivity.h"
#include "ScreenManager.h"
#include "Grapher.h"


GameActivity::GameActivity(int width, int height):Activity(width, height){
}

GameActivity::GameActivity(Escenario escenario, int width, int height):Activity(escenario, width, height){
}

GameActivity::~GameActivity(){
}


void GameActivity::onLoad(){
	
	// texto del tiempo
	this->timeTitle = new RichTextView("Time", RichTextView::NORMAL);
	this->timeTitle->setX(50); this->timeTitle->setY(0);

	// texto de los puntos
	this->pointsTitle = new RichTextView("Points", RichTextView::NORMAL);
	this->pointsTitle->setX(300); this->pointsTitle->setY(0);

	this->period = 2000.0 / 60;
	//this->screenManager = new ScreenManager(this, "Images/fondo.bmp");
	Image* imgBackgroung = new Image("Images/fondo.bmp");

	int imageHeight = (480 / 28);
	
	// this->imageWidth = windowWidth / grilla.getAncho();
	int imageWidth = imageHeight;

	Grapher grapher;
	grapher.setVideoMode(640);
	Image* fondo = grapher.draw(this->getEscenario());

	//this->screenManager = new ScreenManager(this, fondo, this->getEscenario().getGrilla(), imageHeight, imageWidth);
	//this->screenManager->startGame();

	/*ScreenManager s(w, fondo, escenario.getGrilla(), grapher.getImageHeight(), grapher.getImageWidth());
				s.startGame();*/
	
	// los agrego a la pantalla
	this->add(this->timeTitle);
	this->add(this->pointsTitle);
	
	
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
					nextActivity = new MenuActivity(this->getWidth(), this->getHeight());
					break;
				default:
					screenManager->handleKeyStroke();
					
			}
			break;
	}

	screenManager->updateScreen();

	return nextActivity;
}