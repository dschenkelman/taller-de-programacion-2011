#include "StdAfx.h"
#include "MenuActivity.h"
#include "Activity.h"
#include "GameActivity.h"

void MenuActivity::onLoad(){
	
	// titulo y cabecera
	this->banner = new Image("images/title-pacman.bmp");
	this->title = new RichText("pacman", RichText::NORMAL);
	
	// menu con flecha
	this->arrowMenu = new UIOptionArrowMenu();
	this->arrowMenu->addOption("start");
	this->arrowMenu->addOption("quit");

	// los agrego a la pantalla
	this->add(this->banner, 0, 0);
	this->add(this->title, 100, 50);
	this->add(this->arrowMenu, 50, 200);

}

void MenuActivity::notify(SDL_Event e){

	switch(e.type){
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym){
				case SDLK_RETURN:
						{
					//std::string optionTxt = this->arrowMenu->getOption();
					
					
					SDL_Surface *screen2;
					 
					screen2 = SDL_SetVideoMode(640, 480, 24, SDL_DOUBLEBUF);
					
					/*GameActivity* game = new GameActivity();
					game->init();*/
					Image* dualBanner = new Image("images/dual.bmp");
					
					SDL_BlitSurface(dualBanner->getSDLSurface(), NULL, screen2, NULL);
					SDL_Flip(screen2);
					//free(game);
					SDL_Delay(2000);
					break;
						 }
				default:
					this->arrowMenu->notify(e);
					this->add(this->arrowMenu, 50, 200);
					SDL_Flip(this->getSDLSurface());
					break;
			}
			break;
	}



}