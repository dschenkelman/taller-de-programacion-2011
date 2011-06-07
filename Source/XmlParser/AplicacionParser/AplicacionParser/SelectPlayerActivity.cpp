#include "StdAfx.h"
#include "SelectPlayerActivity.h"
#include "DAO.h"
#include "GameActivity.h"
#include "InsertPasswordActivity.h"
#include "CreatePlayerActivity.h"
#include "ComparisonBetweenPlayersActivity.h"

using namespace std;

SelectPlayerActivity::SelectPlayerActivity(int width, int height, Escenario* escenario, bool game):Activity(escenario, width, height)
{
	this->playersQty = 0;
	this->menuPlayerOneActive = true;
	this->menuPlayerTwoActive = false;
	this->escenario = escenario;
	this->game = game;
}

SelectPlayerActivity::SelectPlayerActivity(int width, int height, bool game):Activity(width, height)
{
	this->playersQty = 0;
	this->menuPlayerOneActive = true;
	this->menuPlayerTwoActive = false;
	this->game = game;
}

void SelectPlayerActivity::onLoad()
{
	// cabecera
	this->banner = new ImageView("Images/title_pacman_medium.bmp");
	this->banner->setX(5); this->banner->setY(2);
	this->banner->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// titulo
	this->title = new RichTextView("players selection", RichTextView::NEON);
	this->title->setY(100);
	this->title->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// datos
	this->subtitle = new RichTextView("Select player one", RichTextView::NORMAL);
	this->subtitle->setX(10); this->subtitle->setY(160);

	// player one
	this->arrowMenuPlayerOne = new OptionArrowMenuView();
	this->arrowMenuPlayerOne->setX(50);
	this->arrowMenuPlayerOne->setY(200);

	//player two
	this->arrowMenuPlayerTwo = new OptionArrowMenuView();
	this->arrowMenuPlayerTwo->setX(this->getWidth() - 250);
	this->arrowMenuPlayerTwo->setY(200);
	
	DAO d("gamelog.sql");
	query* players = d.getPlayers();

	while(!players->next())
	{
		this->playersQty++;
		this->arrowMenuPlayerOne->addOption(players->getChars(1));
		this->arrowMenuPlayerTwo->addOption(players->getChars(1));
	}

	delete players;

	this->add(this->banner);
	this->add(this->title);
	this->add(this->subtitle);
	this->add(this->arrowMenuPlayerOne);
	this->add(this->arrowMenuPlayerTwo);
}

Activity* SelectPlayerActivity::notify(SDL_Event e)
{
	if (this->playersQty < 2) return new CreatePlayerActivity(this->getWidth(),this->getHeight());
	Activity* nextActivity = NULL;

	switch(e.type){
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym){
				case SDLK_RETURN:
					if(this->menuPlayerOneActive)
					{
						this->menuPlayerOneActive = false;
						this->menuPlayerTwoActive = true;
						RichTextView* newRtv = new RichTextView("Select player two", RichTextView::NORMAL);
						newRtv->setX(this->getWidth() - 300); newRtv->setY(160);
						this->updateViewFromView(this->subtitle, newRtv);
						delete this->subtitle;
						this->subtitle = newRtv;
					}

					else if(this->menuPlayerTwoActive)
					{
						if(!(this->arrowMenuPlayerTwo->getSelectedOption() ==
							this->arrowMenuPlayerOne->getSelectedOption()))
						{
							this->menuPlayerTwoActive = false;
						}
						/*RichTextView* newRtv = new RichTextView("Players selected", RichTextView::NORMAL);
						newRtv->setX(this->getWidth()/2 - 145); newRtv->setY(this->getHeight() - 50);
						this->updateViewFromView(this->subtitle, newRtv);*/
					}

					if(!(this->menuPlayerOneActive || this->menuPlayerTwoActive))
					{
						if(game)
						{
							nextActivity = new InsertPasswordActivity(this->getWidth(), this->getHeight(),
								this->arrowMenuPlayerOne->getSelectedOption(), this->arrowMenuPlayerTwo->getSelectedOption());
						}

						else
						{
							nextActivity = new ComparisonBetweenPlayersActivity(this->getWidth(), this->getHeight(),
								this->arrowMenuPlayerOne->getSelectedOption(), this->arrowMenuPlayerTwo->getSelectedOption());
						}
					}

					break;
				
				case SDLK_UP:

					if(this->menuPlayerOneActive && !this->menuPlayerTwoActive)
					{
						this->arrowMenuPlayerOne->arrowUp();
					}

					if(this->menuPlayerTwoActive && !this->menuPlayerOneActive)
					{
						this->arrowMenuPlayerTwo->arrowUp();
					}
					
					break;
		
				case SDLK_DOWN:
					if(this->menuPlayerOneActive && !this->menuPlayerTwoActive)
					{
						this->arrowMenuPlayerOne->arrowDown();
					}

					if(this->menuPlayerTwoActive && !this->menuPlayerOneActive)
					{
						this->arrowMenuPlayerTwo->arrowDown();
					}

					break;
			}

			break;

	}

	return nextActivity;
}

SelectPlayerActivity::~SelectPlayerActivity(void)
{
}