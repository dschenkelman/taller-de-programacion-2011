#include "StdAfx.h"
#include "CreatePlayerActivity.h"
#include "List.h"
#include "DAO.h"
#include "MenuActivity.h"
#include "ExistingUsernameActivity.h"
#include <sstream>
#include "InputTextView.h"

CreatePlayerActivity::CreatePlayerActivity(int width, int height):Activity(width, height)
{
	this->usernameBoxActive = true;
}

CreatePlayerActivity::~CreatePlayerActivity(){

}


void CreatePlayerActivity::onLoad()
{
	// cabecera
	this->banner = new ImageView("Images/title_pacman_medium.bmp");
	this->banner->setX(5); this->banner->setY(2);
	this->banner->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// titulo
	this->title = new RichTextView("Create a new player", RichTextView::NEON);
	this->title->setX(100); this->title->setY(100);
	this->title->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// contenido
	RichTextView* rtvUsername = new RichTextView("Username", RichTextView::NORMAL);
	rtvUsername->setX((this->getWidth()/2) - 200); rtvUsername->setY(200);

	RichTextView* rtvPass = new RichTextView("Password", RichTextView::NORMAL);
	rtvPass->setX((this->getWidth()/2) - 200); rtvPass->setY(260);

	//this->rtvUsernameBox = new RichTextView(this->name, RichTextView::NORMAL);
	this->rtvUsernameBox = new InputTextView("", this->MAX_LENGHT);
	this->rtvUsernameBox->setX((this->getWidth()/2) - 20); this->rtvUsernameBox->setY(200);
	this->rtvUsernameBox->setFocusable(true);
	this->rtvUsernameBox->setFocused(true);

	//this->rtvPassBox = new RichTextView(this->passView, RichTextView::NORMAL);
	this->rtvPassBox = new InputTextView("", this->MAX_LENGHT);
	this->rtvPassBox->setX((this->getWidth()/2) - 20); this->rtvPassBox->setY(260);
	this->rtvPassBox->setFocusable(true);

	this->arrowMenu = new OptionArrowMenuView();
	this->arrowMenu->setVerticalAlign(View::VERTICAL_ALIGN_CENTER); this->arrowMenu->setY(this->getHeight() - 50);
	this->arrowMenu->addOption("create player");
	this->arrowMenu->addOption("return to menu");

	// se agrega a la pantalla
	this->add(this->banner);
	this->add(this->title);
	this->add(this->arrowMenu);
	this->add(rtvUsername);
	this->add(rtvUsernameBox);
	this->add(rtvPass);
	this->add(rtvPassBox);
}

Activity* CreatePlayerActivity::notify(SDL_Event e)
{
	Activity* nextActivity = NULL;
	switch(e.type){
		char letra;
		int y;
		case SDL_KEYDOWN:
			if(e.key.keysym.sym == SDLK_TAB)
			{
				this->usernameBoxActive = !(this->usernameBoxActive);
			}

			letra = this->getKey(e.key);
			
			//backspace
			if(letra == '0')
			{
				if(this->usernameBoxActive)
				{
					if(this->name.size() > 0)
					{
						this->name.erase(this->name.size()-1, 1);
						RichTextView* newRtvUsernameBox = new InputTextView(this->name, this->MAX_LENGHT);
						newRtvUsernameBox->setFocusable(true);
						newRtvUsernameBox->setX(this->rtvUsernameBox->getX());
						newRtvUsernameBox->setY(this->rtvUsernameBox->getY());
						this->updateViewFromView(this->rtvUsernameBox, newRtvUsernameBox);
						delete this->rtvUsernameBox;
						this->rtvUsernameBox = newRtvUsernameBox;
					}
					
				}

				else
				{
					if(this->pass.size() > 0)
					{
						this->pass.erase(this->pass.size()-1, 1);
						this->passView.erase(this->passView.size()-7, 7);	
						RichTextView* newRtvPassBox = new InputTextView(this->passView, this->MAX_LENGHT);
						newRtvPassBox->setFocusable(true);
						newRtvPassBox->setX(this->rtvPassBox->getX());
						newRtvPassBox->setY(this->rtvPassBox->getY());
						this->updateViewFromView(this->rtvPassBox, newRtvPassBox);
						this->rtvPassBox = newRtvPassBox;
					}

				}
			}

			else if(letra == '1'){}

			//enter
			else if(letra == '2')
			{
				if(this->arrowMenu->getSelectedOption() == "return to menu")
				{
					nextActivity = new MenuActivity(this->getWidth(), this->getHeight());
				}
				
				if(this->arrowMenu->getSelectedOption() == "create player")
				{
					if(this->verifyUsername(this->name))
					{
						nextActivity = new ExistingUsernameActivity(this->getWidth(), this->getHeight());
					}
					
					else
					{
						DAO d("gamelog.sql");
						d.createPlayer(name, pass);
						nextActivity = new MenuActivity(this->getWidth(), this->getHeight());
					}
				}
			}

			//letra
			else
			{
				if(this->usernameBoxActive)
				{
					if(this->name.size() < this->MAX_LENGHT)
					{
						this->name += letra;
						RichTextView* newRtvUsernameBox = new InputTextView(this->name, this->MAX_LENGHT);
						newRtvUsernameBox->setFocusable(true);
						newRtvUsernameBox->setX(this->rtvUsernameBox->getX());
						newRtvUsernameBox->setY(this->rtvUsernameBox->getY());
						this->updateViewFromView(this->rtvUsernameBox, newRtvUsernameBox);
						delete this->rtvUsernameBox;
						this->rtvUsernameBox = newRtvUsernameBox;
					}
				}
				else
				{
					if(this->pass.size() < this->MAX_LENGHT)
					{
						this->pass += letra;
						this->passView += "&atrsk;";
						RichTextView* newRtvPassBox = new InputTextView(this->passView, this->MAX_LENGHT);
						newRtvPassBox->setFocusable(true);
						newRtvPassBox->setX(this->rtvPassBox->getX());
						newRtvPassBox->setY(this->rtvPassBox->getY());
						this->updateViewFromView(this->rtvPassBox, newRtvPassBox);
						this->rtvPassBox = newRtvPassBox;
					}
				}
			}

			break;

		case SDL_MOUSEBUTTONDOWN:
			y = e.button.y;
			
			if(y < 240)
			{
				this->usernameBoxActive = true;
			}

			else
			{
				this->usernameBoxActive = false;
			}

			break;
	}

	this->rtvUsernameBox->setFocused(this->usernameBoxActive);
	this->rtvPassBox->setFocused(!(this->usernameBoxActive));

	return nextActivity;
}

bool CreatePlayerActivity::verifyUsername(std::string username)
{
	DAO d("gamelog.sql");
	query* players = d.getPlayers();

	while(!players->next())
	{
		if(strcmp(players->getChars(1), username.c_str()) == 0)
		{
			return true;
		}
	}

	return false;
}

char CreatePlayerActivity::getKey(SDL_KeyboardEvent e)
{
	switch(e.keysym.sym)
	{
		case SDLK_a:
			return 'a';
		case SDLK_b:
			return 'b';
		case SDLK_c:
			return 'c';
		case SDLK_d:
			return 'd';
		case SDLK_e:
			return 'e';
		case SDLK_f:
			return 'f';
		case SDLK_g:
			return 'g';
		case SDLK_h:
			return 'h';
		case SDLK_i:
			return 'i';
		case SDLK_j:
			return 'j';
		case SDLK_k:
			return 'k';
		case SDLK_l:
			return 'l';
		case SDLK_m:
			return 'm';
		case SDLK_n:
			return 'n';
		case SDLK_o:
			return 'o';
		case SDLK_p:
			return 'p';
		case SDLK_q:
			return 'q';
		case SDLK_r:
			return 'r';
		case SDLK_s:
			return 's';
		case SDLK_t:
			return 't';
		case SDLK_u:
			return 'u';
		case SDLK_v:
			return 'v';
		case SDLK_w:
			return 'w';
		case SDLK_x:
			return 'x';
		case SDLK_y:
			return 'y';
		case SDLK_z:
			return 'z';
		case SDLK_BACKSPACE:
			return '0';
		case SDLK_RETURN:
			return '2';
		case SDLK_DOWN:
			this->arrowMenu->arrowDown();
			return '1';
		case SDLK_UP:
			this->arrowMenu->arrowUp();
			return '1';
		default:
			return '1';
	}
}