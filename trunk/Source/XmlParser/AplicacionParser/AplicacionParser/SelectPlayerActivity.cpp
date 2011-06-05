#include "StdAfx.h"
#include "SelectPlayerActivity.h"
#include "DAO.h"
#include "GameActivity.h"

SelectPlayerActivity::SelectPlayerActivity(int width, int height, Escenario* escenario):Activity(escenario, width, height)
{
	this->menuPlayerOneActive = true;
	this->menuPlayerTwoActive = false;
	this->escenario = escenario;
}

SelectPlayerActivity::SelectPlayerActivity(int width, int height):Activity(width, height)
{
	this->menuPlayerOneActive = true;
	this->menuPlayerTwoActive = false;
}

void SelectPlayerActivity::onLoad()
{
	// cabecera
	this->banner = new ImageView("Images/dual.bmp");
	this->banner->setX(5); this->banner->setY(5);
	this->banner->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// titulo
	this->title = new RichTextView("pacman", RichTextView::NORMAL);
	this->title->setY(50);
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
		this->arrowMenuPlayerOne->addOption(players->getChars(1));
		this->arrowMenuPlayerTwo->addOption(players->getChars(1));
	}

	this->add(this->banner);
	this->add(this->title);
	this->add(this->subtitle);
	this->add(this->arrowMenuPlayerOne);
	this->add(this->arrowMenuPlayerTwo);
}

Activity* SelectPlayerActivity::notify(SDL_Event e)
{
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
					}

					else if(this->menuPlayerTwoActive)
					{
						this->menuPlayerTwoActive = false;
						/*RichTextView* newRtv = new RichTextView("Players selected", RichTextView::NORMAL);
						newRtv->setX(this->getWidth()/2 - 145); newRtv->setY(this->getHeight() - 50);
						this->updateViewFromView(this->subtitle, newRtv);*/
					}

					if(!(this->menuPlayerOneActive || this->menuPlayerTwoActive))
					{
						nextActivity = new GameActivity(this->getWidth(), this->getHeight(), 
							this->arrowMenuPlayerOne->getSelectedOption(), this->arrowMenuPlayerTwo->getSelectedOption());
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