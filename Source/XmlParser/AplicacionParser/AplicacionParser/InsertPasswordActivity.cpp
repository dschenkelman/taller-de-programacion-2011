#include "StdAfx.h"
#include "InsertPasswordActivity.h"
#include "InputTextView.h"
#include "SelectPlayerActivity.h"
#include "GameActivity.h"
#include "DAO.h"

InsertPasswordActivity::InsertPasswordActivity(int width, int height, std::string playerOne, std::string playerTwo):Activity(width, height)
{
	this->playerOne = playerOne;
	this->playerTwo = playerTwo;
	this->boxPlayerOneActive = true;
}

void InsertPasswordActivity::onLoad()
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
	this->subtitle = new RichTextView("Password " + this->playerOne, RichTextView::NORMAL);
	this->subtitle->setX(10); this->subtitle->setY(160);

	this->arrowMenu = new OptionArrowMenuView();
	this->arrowMenu->setX(this->getWidth()/2 - 85); this->arrowMenu->setY(this->getHeight() - 60);
	this->arrowMenu->addOption("start game");
	this->arrowMenu->addOption("back");

	this->passBoxPlayerOne = new InputTextView("", 5);
	this->passBoxPlayerOne->setX(50); this->passBoxPlayerOne->setY(190);

	this->passBoxPlayerTwo = new InputTextView("", 5);
	this->passBoxPlayerTwo->setX(this->getWidth()/2 + 50); this->passBoxPlayerTwo->setY(190);

	//agrego a la pantalla
	this->add(this->banner);
	this->add(this->title);
	this->add(this->subtitle);
	this->add(this->arrowMenu);
	this->add(this->passBoxPlayerOne);
	this->add(this->passBoxPlayerTwo);
}

Activity* InsertPasswordActivity::notify(SDL_Event e)
{
	Activity* nextActivity = NULL;

	switch(e.type){
		case SDL_KEYDOWN:
			char letra = this->getKey(e.key);
			
			//backspace
			if(letra == '0')
			{
				this->removeView(this->msg);

				if(this->boxPlayerOneActive)
				{
					if(this->passPlayerOne.size() > 0)
					{
						this->passPlayerOne.erase(this->passPlayerOne.size()-1, 1);
						this->passPlayerOneView.erase(this->passPlayerOneView.size()-7, 7);
						RichTextView* newPass = new InputTextView(this->passPlayerOneView, 5);
						newPass->setX(this->passBoxPlayerOne->getX());
						newPass->setY(this->passBoxPlayerOne->getY());
						this->updateViewFromView(this->passBoxPlayerOne, newPass);
						delete this->passBoxPlayerOne;
						this->passBoxPlayerOne = newPass;
					}
				}

				else
				{
					if(this->passPlayerTwo.size() > 0)
					{
						this->passPlayerTwo.erase(this->passPlayerTwo.size()-1, 1);
						this->passPlayerTwoView.erase(this->passPlayerTwoView.size()-7, 7);
						RichTextView* newPass = new InputTextView(this->passPlayerTwoView, 5);
						newPass->setX(this->passBoxPlayerTwo->getX());
						newPass->setY(this->passBoxPlayerTwo->getY());
						this->updateViewFromView(this->passBoxPlayerTwo, newPass);
						delete this->passBoxPlayerTwo;
						this->passBoxPlayerTwo = newPass;
					}
				}
			}

			//arriba, abajo y default
			else if(letra == '1')
			{
				this->removeView(this->msg);
			}

			//enter
			else if(letra == '2')
			{
				this->removeView(this->msg);

				if(this->arrowMenu->getSelectedOption() == "back")
				{
					nextActivity = new SelectPlayerActivity(this->getWidth(), this->getHeight(), true);
				}
					
				else
				{
					if(this->boxPlayerOneActive)
					{
						// verificar que la contraseña sea correcta
						// si no lo es, mostrar cartel de incorrecto
						// si es, mostrar cartel de correcto y poner
						// this->boxPlayerOneActive en false
						if(this->passPlayerOne == this->getPassword(this->playerOne))
						{
							RichTextView* newSubtitle = new RichTextView("Password " + this->playerTwo, RichTextView::NORMAL);
							newSubtitle->setX(this->getWidth()/2 + 50); newSubtitle->setY(this->subtitle->getY());
							this->updateViewFromView(this->subtitle, newSubtitle);
							delete this->subtitle;
							this->subtitle = newSubtitle;
							this->boxPlayerOneActive = false;
							RichTextView* correctMsg = new RichTextView("Correct password", RichTextView::NORMAL);
							correctMsg->setX(10); correctMsg->setY(210);
							this->add(correctMsg);
						}

						else
						{
							this->passPlayerOne = "";
							this->passPlayerOneView = "";
							RichTextView* newPass = new InputTextView(this->passPlayerOneView, 5);
							newPass->setX(this->passBoxPlayerOne->getX());
							newPass->setY(this->passBoxPlayerOne->getY());
							this->updateViewFromView(this->passBoxPlayerOne, newPass);
							delete this->passBoxPlayerOne;
							this->passBoxPlayerOne = newPass;
							this->msg = new RichTextView("Incorrect password", RichTextView::NORMAL);
							this->msg->setX(10); this->msg->setY(210);
							this->add(this->msg);
						}
					}

					else
					{
						if(this->passPlayerTwo == this->getPassword(this->playerTwo))
						{
							RichTextView* correctMsg = new RichTextView("Correct password", RichTextView::NORMAL);
							correctMsg->setX(10); correctMsg->setY(210);
							this->add(correctMsg);
							nextActivity = new GameActivity(this->getWidth(), this->getHeight(), 
								this->playerOne, this->playerTwo);
						}
						
						else
						{
							this->passPlayerTwo = "";
							this->passPlayerTwoView = "";
							RichTextView* newPass = new InputTextView(this->passPlayerTwoView, 5);
							newPass->setX(this->passBoxPlayerTwo->getX());
							newPass->setY(this->passBoxPlayerTwo->getY());
							this->updateViewFromView(this->passBoxPlayerTwo, newPass);
							delete this->passBoxPlayerTwo;
							this->passBoxPlayerTwo = newPass;
							this->msg = new RichTextView("Incorrect password", RichTextView::NORMAL);
							this->msg->setX(this->getWidth()/2 + 10); this->msg->setY(210);
							this->add(this->msg);
						}
						
					}
				}
			}

			//letra
			else
			{
				this->removeView(this->msg);

				if(this->boxPlayerOneActive)
				{
					if(this->passPlayerOne.size() < 5)
					{
						this->passPlayerOne += letra;
						this->passPlayerOneView += "&atrsk;";
						RichTextView* newRtvPassBox = new InputTextView(this->passPlayerOneView, 5);
						newRtvPassBox->setX(this->passBoxPlayerOne->getX());
						newRtvPassBox->setY(this->passBoxPlayerOne->getY());
						this->updateViewFromView(this->passBoxPlayerOne, newRtvPassBox);
						delete this->passBoxPlayerOne;
						this->passBoxPlayerOne = newRtvPassBox;
					}
				}

				else
				{
					if(this->passPlayerTwo.size() < 5)
					{
						this->passPlayerTwo += letra;
						this->passPlayerTwoView += "&atrsk;";
						RichTextView* newRtvPassBox = new InputTextView(this->passPlayerTwoView, 5);
						newRtvPassBox->setX(this->passBoxPlayerTwo->getX());
						newRtvPassBox->setY(this->passBoxPlayerTwo->getY());
						this->updateViewFromView(this->passBoxPlayerTwo, newRtvPassBox);
						delete this->passBoxPlayerTwo;
						this->passBoxPlayerTwo = newRtvPassBox;
					}
				}
			}

			break;
	}

	return nextActivity;
}

char InsertPasswordActivity::getKey(SDL_KeyboardEvent e)
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

std::string InsertPasswordActivity::getPassword(std::string name)
{
	DAO d("gamelog.sql");
	return d.getPassword(name);
}