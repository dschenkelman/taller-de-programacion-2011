#include "StdAfx.h"
#include "GameActivity.h"
#include "Activity.h"
#include "MenuActivity.h"
#include "ScreenManager.h"
#include "Grapher.h"
#include <iostream>
#include "XmlParser.h"

GameActivity::GameActivity(int width, int height):Activity(width, height){
}

GameActivity::GameActivity(Escenario* escenario, int width, int height):Activity(escenario, width, height){
}

GameActivity::~GameActivity()
{
	delete this->fondo;
	delete this->escenario;
	/*delete this->timeTitle;
	delete this->pointsTitle;*/
	delete this->screenManager;
}


void GameActivity::onLoad(){
	
	this->period = 1000.0 / 60;

	char* fileName = "escenarioPacman.xml";

	ifstream ifile(fileName);
	ifile.close();
	XmlParser parser;
	string name = fileName;
	parser.openFile(name);
	XmlElement* root = parser.parse();
	parser.closeFile();
	
	this->escenario = new Escenario(*root);
	Grapher grapher;
	grapher.setVideoMode(this->getWidth());
	this->fondo = grapher.draw(*this->escenario);

	int posX = (grapher.getImageWidth() * this->escenario->getGrilla().getAncho())+10;

	// texto del tiempo
	this->timeTitle = new RichTextView("Time", RichTextView::NORMAL);
	this->timeTitle->setX(posX); this->timeTitle->setY(0);

	// texto de los puntos
	this->pointsTitle = new RichTextView("Points", RichTextView::NORMAL);
	this->pointsTitle->setX(posX); this->pointsTitle->setY(50);

	// Creo un screenmanager para la logica del juego
	this->screenManager = new ScreenManager(this, fondo, this->escenario->getGrilla(), grapher.getImageHeight(), grapher.getImageWidth());

	// los agrego a la pantalla
	this->add(this->timeTitle);
	this->add(this->pointsTitle);
}


// En el update de esta actividad hago el update del juego
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