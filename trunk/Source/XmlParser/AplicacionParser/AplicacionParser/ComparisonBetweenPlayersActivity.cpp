#include "StdAfx.h"
#include "ComparisonBetweenPlayersActivity.h"
#include "DAO.h"
#include <sstream>
#include "StatsActivity.h"

ComparisonBetweenPlayersActivity::ComparisonBetweenPlayersActivity(int width, int height, 
		std::string playerOne, std::string playerTwo):Activity(width, height)
{
	this->playerOne = playerOne;
	this->playerTwo = playerTwo;
}

void ComparisonBetweenPlayersActivity::onLoad()
{
	// cabecera
	this->banner = new ImageView("Images/dual.bmp");
	this->banner->setX(5); this->banner->setY(5);
	this->banner->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// titulo
	this->title = new RichTextView("Comparison between players", RichTextView::NORMAL);
	this->title->setY(50);
	this->title->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	bool games = this->initializeAttributes();

	if(games)
	{
		// botones atrás y adelante. reemplazar por una piola imagen
		ImageView* previousButton = new ImageView("Images/flechaizq.bmp");
		previousButton->setX(10); previousButton->setY(150);

		ImageView* nextButton = new ImageView("Images/flechader.bmp");
		nextButton->setX(this->getWidth() - 50); nextButton->setY(150);

		// subtitulo
		RichTextView* rtvTitle = new RichTextView("Game ", RichTextView::NORMAL);
		rtvTitle->setX(this->getWidth()/2 - 65); rtvTitle->setY(160);
		
		std::stringstream gameNumberStr;
		gameNumberStr << (this->gameNumber + 1);
		this->gameNumberRTV = new RichTextView(gameNumberStr.str(), RichTextView::NORMAL);
		this->gameNumberRTV->setX(this->getWidth()/2 + 50); this->gameNumberRTV->setY(160);

		// encabezados
		RichTextView* playersHeader = new RichTextView("Players", RichTextView::NEON);
		playersHeader->setX(this->getWidth()/2 - 280); playersHeader->setY(210);

		RichTextView* winnerHeader = new RichTextView("Winner", RichTextView::NEON);
		winnerHeader->setX(this->getWidth()/2 - 140); winnerHeader->setY(210);

		RichTextView* pointsHeader = new RichTextView("Points", RichTextView::NEON);
		pointsHeader->setX(this->getWidth()/2); pointsHeader->setY(210);

		RichTextView* durationHeader = new RichTextView("Duration", RichTextView::NEON);
		durationHeader->setX(this->getWidth()/2 + 140); durationHeader->setY(210);

		RichTextView* rtvPlayerOne = new RichTextView(this->playerOne, RichTextView::NORMAL);
		rtvPlayerOne->setX(this->getWidth()/2 - 280); rtvPlayerOne->setY(230);

		RichTextView* rtvPlayerTwo = new RichTextView(this->playerTwo, RichTextView::NORMAL);
		rtvPlayerTwo->setX(this->getWidth()/2 - 280); rtvPlayerTwo->setY(250);

		//datos
		this->pointsPlayerOneRTV = new RichTextView(this->pointsPlayerOne, RichTextView::NORMAL);
		this->pointsPlayerOneRTV->setX(this->getWidth()/2); this->pointsPlayerOneRTV->setY(230);

		this->pointsPlayerTwoRTV = new RichTextView(this->pointsPlayerTwo, RichTextView::NORMAL);
		this->pointsPlayerTwoRTV->setX(this->getWidth()/2); this->pointsPlayerTwoRTV->setY(250);

		this->timeRTV = new RichTextView(this->time, RichTextView::NORMAL);
		this->timeRTV->setX(this->getWidth()/2 + 140); this->timeRTV->setY(240);

		this->winnerRTV = new RichTextView(this->winner, RichTextView::NORMAL);
		this->winnerRTV->setX(this->getWidth()/2 - 140); this->winnerRTV->setY(240);

		this->add(this->pointsPlayerOneRTV);
		this->add(this->pointsPlayerTwoRTV);
		this->add(this->timeRTV);
		this->add(this->winnerRTV);
		this->add(this->gameNumberRTV);
		this->add(rtvTitle);
		this->add(previousButton);
		this->add(nextButton);
		this->add(playersHeader);
		this->add(winnerHeader);
		this->add(pointsHeader);
		this->add(durationHeader);
		this->add(rtvPlayerOne);
		this->add(rtvPlayerTwo);
	}

	else
	{
		RichTextView* msg = new RichTextView("No games founded", RichTextView::NORMAL);
		msg->setX(this->getWidth()/2 - 186); msg->setY(this->getHeight()/2 - 50);
		this->add(msg);
	}

	// arrow menu
	this->arrowMenu = new OptionArrowMenuView();
	this->arrowMenu->addOption("return to stats");
	this->arrowMenu->setY(this->getHeight() - 50); this->arrowMenu->setX(this->getWidth()/2 - 150);

	//agrego a la pantalla
	this->add(this->banner);
	this->add(this->title);
	this->add(this->arrowMenu);
}

Activity* ComparisonBetweenPlayersActivity::notify(SDL_Event e)
{
	Activity* nextActivity = NULL;
	int y;
	int x;

	switch(e.type){
		case SDL_KEYDOWN:
			if(e.key.keysym.sym == SDLK_RIGHT)
			{
				this->updateAttributes(true);
				this->updateRTV();
			}

			else if(e.key.keysym.sym == SDLK_LEFT)
			{
				this->updateAttributes(false);
				this->updateRTV();
			}

			else if(e.key.keysym.sym == SDLK_RETURN)
			{
				if(this->arrowMenu->getSelectedOption() == "return to stats")
				{
					nextActivity = new StatsActivity(this->getWidth(), this->getHeight());
				}
			}

			else
			{
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			y = e.button.y;
			x = e.button.x;
			if(x > 10 && x < 50 && y > 150 && y < 190)
			{
				this->updateAttributes(false);
				this->updateRTV();
			}

			else if(x > (this->getWidth() - 50) && x < (this->getWidth() - 10) && y > 150 && y < 190)
			{
				this->updateAttributes(true);
				this->updateRTV();
			}

		default:
			break;
	}
	
	return nextActivity;
}

bool ComparisonBetweenPlayersActivity::initializeAttributes()
{
	bool ret = false;

	DAO d("gamelog.sql");
	query* stats = d.getComparisonBetweenPlayers(this->playerOne, this->playerTwo);
	
	while(!stats->next())
	{
		game game;
		game.playerOne = stats->getChars(0);
		game.playerTwo = stats->getChars(1);
		game.pointsOne = stats->getInt(2);
		game.pointsTwo = stats->getInt(3);
		game.winner = stats->getChars(4);
		game.time = stats->getInt(5);

		this->gamesList.add(game);
		ret = true;
	}

	this->gameNumber = -1;
	
	if(ret)
	{
		this->updateAttributes(true);
	}

	return ret;
}

void ComparisonBetweenPlayersActivity::updateAttributes(bool next)
{
	if(next)
	{
		if(this->gameNumber == this->gamesList.length() - 1)
		{
			this->gameNumber = 0;
		}

		else
		{
			this->gameNumber++;
		}
	}

	else
	{
		if(this->gameNumber == 0)
		{
			this->gameNumber = this->gamesList.length() - 1;
		}

		else
		{
			this->gameNumber--;
		}
	}
	
	std::stringstream ptsOne;
	if(this->gamesList.at(this->gameNumber).pointsOne < 0)
	{
		this->gamesList.at(this->gameNumber).pointsOne = abs(this->gamesList.at(this->gameNumber).pointsOne);
		ptsOne << "&udash;";
	}
	ptsOne << this->gamesList.at(this->gameNumber).pointsOne;
	this->pointsPlayerOne = ptsOne.str();

	std::stringstream ptsTwo;
	if(this->gamesList.at(this->gameNumber).pointsTwo < 0)
	{
		this->gamesList.at(this->gameNumber).pointsTwo = abs(this->gamesList.at(this->gameNumber).pointsTwo);
		ptsOne << "&udash;";
	}
	ptsTwo << this->gamesList.at(this->gameNumber).pointsTwo;
	this->pointsPlayerTwo = ptsTwo.str();

	std::stringstream timeStr;
	timeStr << this->gamesList.at(this->gameNumber).time;
	this->time = timeStr.str();

	this->winner = this->gamesList.at(this->gameNumber).winner;
}

void ComparisonBetweenPlayersActivity::updateRTV()
{
	// actualiza puntos jugador uno
	RichTextView* newPointsOne = new RichTextView(this->pointsPlayerOne, RichTextView::NORMAL);
	newPointsOne->setX(this->pointsPlayerOneRTV->getX());
	newPointsOne->setY(this->pointsPlayerOneRTV->getY());
	this->updateViewFromView(this->pointsPlayerOneRTV, newPointsOne);
	delete this->pointsPlayerOneRTV;
	this->pointsPlayerOneRTV = newPointsOne;

	// actualiza puntos jugador dos
	RichTextView* newPointsTwo = new RichTextView(this->pointsPlayerTwo, RichTextView::NORMAL);
	newPointsTwo->setX(this->pointsPlayerTwoRTV->getX());
	newPointsTwo->setY(this->pointsPlayerTwoRTV->getY());
	this->updateViewFromView(this->pointsPlayerTwoRTV, newPointsTwo);
	delete this->pointsPlayerTwoRTV;
	this->pointsPlayerTwoRTV = newPointsTwo;

	// actualiza tiempo
	RichTextView* newTime = new RichTextView(this->time, RichTextView::NORMAL);
	newTime->setX(this->timeRTV->getX());
	newTime->setY(this->timeRTV->getY());
	this->updateViewFromView(this->timeRTV, newTime);
	delete this->timeRTV;
	this->timeRTV = newTime;

	// actualiza ganador
	RichTextView* newWinner = new RichTextView(this->winner, RichTextView::NORMAL);
	newWinner->setX(this->winnerRTV->getX());
	newWinner->setY(this->winnerRTV->getY());
	this->updateViewFromView(this->winnerRTV, newWinner);
	delete this->winnerRTV;
	this->winnerRTV = newWinner;

	// actualiza numero de partido
	std::stringstream gn;
	gn << this->gameNumber;
	RichTextView* newGame = new RichTextView(gn.str(), RichTextView::NORMAL);
	newGame->setX(this->gameNumberRTV->getX());
	newGame->setY(this->gameNumberRTV->getY());
	this->updateViewFromView(this->gameNumberRTV, newGame);
	delete this->gameNumberRTV;
	this->gameNumberRTV = newGame;
}

ComparisonBetweenPlayersActivity::~ComparisonBetweenPlayersActivity(void)
{
}
