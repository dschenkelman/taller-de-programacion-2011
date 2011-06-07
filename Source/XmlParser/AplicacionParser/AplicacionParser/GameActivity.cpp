#include "StdAfx.h"
#include "GameActivity.h"
#include "Activity.h"
#include "MenuActivity.h"
#include "ScreenManager.h"
#include "Grapher.h"
#include <iostream>
#include "XmlParser.h"
#include <sstream>
#include <algorithm>

GameActivity::GameActivity(int width, int height):Activity(width, height),
points1(0), points2(0), xCarteles(0), gameTime(0), displayedSeconds(0)
{
	this->errorFound = false;
}

GameActivity::GameActivity(int width, int height, std::string playerOne, std::string playerTwo):Activity(width, height),
points1(0), points2(0), xCarteles(0), gameTime(0), displayedSeconds(0)
{
	this->playerOne = playerOne;
	this->playerTwo = playerTwo;
	this->errorFound = false;
}

GameActivity::GameActivity(Escenario* escenario, int width, int height):Activity(escenario, width, height),
points1(0), points2(0), xCarteles(0), gameTime(0), displayedSeconds(0)
{
}

GameActivity::~GameActivity()
{
	if(!this->errorFound && this->loaded)
	{
		delete this->screenManager;
		delete this->escenario;
		delete this->fondo;
		delete this->loadingTxt;
		/*delete this->timeTitle;
		delete this->pointsTitle;*/
	}
}



void GameActivity::onLoad(){

	this->period = 1000.0 / 60;
	this->errorFound = false;
	this->loaded = false;
	
	this->loadingTxt = new RichTextView("loading&sdot;&sdot;&sdot;", RichTextView::NORMAL);
	this->loadingTxt->setY(300);
	this->loadingTxt->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);
	this->add(loadingTxt);

}

void GameActivity::loadGame(){
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

				this->xCarteles = (grapher.getImageWidth() * this->escenario->getGrilla()->getAncho())+10;

				// texto del tiempo
				this->timeTitle = new RichTextView("Time", RichTextView::NORMAL);
				this->timeTitle->setX(this->xCarteles); this->timeTitle->setY(0);

				this->secondsView = new RichTextView("0", RichTextView::NORMAL);
				this->secondsView->setX(this->xCarteles); this->secondsView->setY(25);

				// texto de los puntos jugador 1
				//this->points1Title = new RichTextView("Yellow Pac", RichTextView::NORMAL);
				this->points1Title = new RichTextView(this->playerOne, RichTextView::NORMAL);
				this->points1Title->setX(this->xCarteles); this->points1Title->setY(50);

				this->points1View = new RichTextView("0", RichTextView::NORMAL);
				this->points1View->setX(this->xCarteles); this->points1View->setY(75);

				// texto de los puntos jugador 2
				//this->points2Title = new RichTextView("Red Pac", RichTextView::NORMAL);
				this->points2Title = new RichTextView(this->playerTwo, RichTextView::NORMAL);
				this->points2Title->setX(this->xCarteles); this->points2Title->setY(100);

				this->points2View = new RichTextView("0", RichTextView::NORMAL);
				this->points2View->setX(this->xCarteles); this->points2View->setY(125);

				// antes de mostrar el juego borro el texto loading
				this->removeView(this->loadingTxt);

				// Creo un screenmanager para la logica del juego
				this->screenManager = new ScreenManager(this, this->fondo, this->escenario->getGrilla(), grapher.getImageHeight(), grapher.getImageWidth(), this->period);

				// los agrego a la pantalla
				this->add(this->timeTitle);
				this->add(this->points1Title);
				this->add(this->points2Title);
				this->add(this->secondsView);
				this->add(this->points1View);
				this->add(this->points2View);
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
void GameActivity::update()
{
	if(!this->errorFound && this->loaded)
	{
		if (!this->screenManager->gameOver())
		{
			this->gameTime += this->period;
		}
		screenManager->updateScreen();
		this->updateScoreBoard();
	}
}
Activity* GameActivity::notify(SDL_Event e){
	
	if(!this->loaded){
		this->loadGame();
		this->loaded = true;
		return NULL;
	}
	
	Activity* nextActivity = NULL;

	switch(e.type){
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym){
				case SDLK_RETURN:
					nextActivity = new MenuActivity(this->getWidth(), this->getHeight());
					break;
				default:
					if(!this->errorFound && this->loaded){
						screenManager->handleKeyStroke();
						if (this->screenManager->gameOver())
						{
							nextActivity = new MenuActivity(this->getWidth(), this->getHeight());
						}
						// screenManager->updateScreen();
					}
				
			}
			break;
	}

	if (this->screenManager->gameOver())
	{
		nextActivity = new MenuActivity(this->getWidth(), this->getHeight());
	}
	else
	{
		screenManager->updateScreen();
	}

	return nextActivity;
}

void GameActivity::updateScoreBoard(void)
{

	int pacman1Score = screenManager->getPacman1()->getScore();
	int pacman2Score = screenManager->getPacman2()->getScore();
	
	if (this->points1 != pacman1Score)
	{
		this->points1 = pacman1Score;
		stringstream ss;//create a stringstream
		ss << pacman1Score;//add number to the stream
		string score  = ss.str();
		
		if (score.at(0) == '-')
		{
			score = "&mdash;" + score.substr(1);
		}

		RichTextView* updatedPoints1View = new RichTextView(score, RichTextView::NORMAL);
		updatedPoints1View->setX(this->xCarteles); updatedPoints1View->setY(75);

		this->updateViewFromView(this->points1View, updatedPoints1View);

		delete this->points1View;
		this->points1View = updatedPoints1View;
	}

	if (this->points2 != pacman2Score)
	{
		this->points2 = pacman2Score;
		stringstream ss;
		ss << pacman2Score;

		string score  = ss.str();

		if (score.at(0) == '-')
		{
			score = "&mdash;" + score.substr(1);
		}

		RichTextView* updatedPoints2View = new RichTextView(score, RichTextView::NORMAL);
		updatedPoints2View->setX(this->xCarteles); updatedPoints2View->setY(125);

		this->updateViewFromView(this->points2View, updatedPoints2View);

		delete this->points2View;
		this->points2View = updatedPoints2View;
	}

	if ((this->gameTime / 1000) != this->displayedSeconds)
	{
		this->displayedSeconds = this->gameTime / 1000;

		stringstream ss;
		ss << this->displayedSeconds;

		string seconds  = ss.str();

		RichTextView* updatedSecondsView = new RichTextView(seconds, RichTextView::NORMAL);
		updatedSecondsView->setX(this->xCarteles); updatedSecondsView->setY(25);

		this->updateViewFromView(this->secondsView, updatedSecondsView);

		delete this->secondsView;
		this->secondsView = updatedSecondsView;
	}
}