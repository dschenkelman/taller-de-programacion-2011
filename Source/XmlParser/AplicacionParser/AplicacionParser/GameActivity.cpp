#include "StdAfx.h"
#include "GameActivity.h"
#include "Activity.h"
#include "MenuActivity.h"
#include "ScreenManager.h"
#include "Grapher.h"
#include <iostream>
#include "XmlParser.h"

GameActivity::GameActivity(int width, int height):Activity(width, height){
	this->errorFound = false;
}

GameActivity::GameActivity(Escenario* escenario, int width, int height):Activity(escenario, width, height){
}

GameActivity::~GameActivity()
{
	if(!this->errorFound){
		delete this->screenManager;
		delete this->escenario;
		delete this->fondo;
		/*delete this->timeTitle;
		delete this->pointsTitle;*/
	}
}


void GameActivity::onLoad(){

	this->period = 1000.0 / 60;
	
	char* fileName = "escenarioPacman.xml";
	ifstream ifile(fileName);
	if (ifile) 
	{
		//The file exists, and is open for input
		ifile.close();
		XmlParser parser;
		string name = fileName;
		parser.openFile(name);
		XmlElement* root = parser.parse();
		parser.closeFile();
		this->escenario = new Escenario(*root);
		delete root;
		if (!this->escenario->hasError()){
			Grapher grapher;
			grapher.setVideoMode(this->getWidth());
			this->fondo = grapher.draw(*this->escenario);

			if (!grapher.hasError()){

				int posX = (grapher.getImageWidth() * this->escenario->getGrilla()->getAncho())+10;

				// texto del tiempo
				this->timeTitle = new RichTextView("Time", RichTextView::NORMAL);
				this->timeTitle->setX(posX); this->timeTitle->setY(0);

				// texto de los puntos
				this->pointsTitle = new RichTextView("Points", RichTextView::NORMAL);
				this->pointsTitle->setX(posX); this->pointsTitle->setY(50);

				// Creo un screenmanager para la logica del juego
				this->screenManager = new ScreenManager(this, fondo, this->escenario->getGrilla(), grapher.getImageHeight(), grapher.getImageWidth(), this->period);

				// los agrego a la pantalla
				this->add(this->timeTitle);
				this->add(this->pointsTitle);

			}
			else{
				std::string msg = "Error al graficar. Ver el archivo parser.log.txt";
				RichTextView* errorTxt = new RichTextView(msg, RichTextView::NORMAL);
				errorTxt->setY(200);
				errorTxt->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);
				this->add(errorTxt);
				
				RichTextView* enter = new RichTextView("press enter", RichTextView::NORMAL);
				enter->setY(250);
				enter->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);
				this->add(enter);
				
				this->errorFound = true;
			}
		}else{
			std::string msg = "Error al imprimir el Escenario. Referirse a parser.log.txt para mas detalles.";
			RichTextView* errorTxt = new RichTextView(msg, RichTextView::NORMAL);
			errorTxt->setY(200);
			errorTxt->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);
			this->add(errorTxt);
			RichTextView* enter = new RichTextView("press enter", RichTextView::NORMAL);
			enter->setY(250);
			enter->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);
			this->add(enter);

			this->errorFound = true;
		}
	}else{
		std::string msg = "El archivo: sarasa no existe.";
		RichTextView* errorTxt = new RichTextView(msg, RichTextView::NORMAL);
		errorTxt->setY(200);
		errorTxt->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);
		this->add(errorTxt);
		RichTextView* enter = new RichTextView("press enter", RichTextView::NORMAL);
		enter->setY(250);
		enter->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);
		this->add(enter);

		this->errorFound = true;
	}

}


// En el update de esta actividad hago el update del juego
void GameActivity::update(){
	if(!this->errorFound)
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
					if(!this->errorFound){
						screenManager->handleKeyStroke();
						if (this->screenManager->gameOver())
						{
							nextActivity = new MenuActivity(this->getWidth(), this->getHeight());
						}
						//screenManager->updateScreen();
					}
					
			}
			break;
	}
	return nextActivity;
}