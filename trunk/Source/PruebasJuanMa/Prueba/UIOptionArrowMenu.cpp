#include "StdAfx.h"
#include "UIOptionArrowMenu.h"
#include "RichText.h"

UIOptionArrowMenu::UIOptionArrowMenu(): Image(0,0){
	this->optionsCount = 0;
	Image* aux = new Image(300, 200);
	this->copy(*aux);
	this->arrowX = 0;
	this->arrowY = 0;
	this->arrow = new Image("images/menu-arrow.bmp");
	
	SDL_Rect* rec = new SDL_Rect();
	rec->h = this->arrow->getHeight();
	rec->w = this->arrow->getWidth();
	rec->x = this->arrowX;
	rec->y = this->arrowY;
	SDL_BlitSurface(this->arrow->getSDLSurface(), NULL, this->getSDLSurface(), rec);
	SDL_Flip(this->getSDLSurface());
}



void UIOptionArrowMenu::addOption(std::string optionTxt){
	
	RichText* newOption = new RichText(optionTxt, RichText::NORMAL);

	SDL_Rect* rec = new SDL_Rect();
	rec->h = newOption->getHeight();
	rec->w = newOption->getWidth();
	rec->x = 50;
	rec->y = (50*this->optionsCount);
	SDL_BlitSurface(newOption->getSDLSurface(), NULL, this->getSDLSurface(), rec);
	SDL_Flip(this->getSDLSurface());
	
	this->optionsCount++;
}



void UIOptionArrowMenu::addListener(){
}


void UIOptionArrowMenu::arrowUp(){
	
	SDL_Rect* rec = new SDL_Rect();
	rec->h = this->arrow->getHeight();
	rec->w = this->arrow->getWidth();

	
	// borro la flecha anterior
	rec->x = this->arrowX;
	rec->y = this->arrowY;
	SDL_FillRect( this->getSDLSurface(), rec, 0);

	// pongo la flecha en la nueva posicion
	rec->x = this->arrowX;
	rec->y = (this->arrowY-20);
	
	this->arrowY = (this->arrowY-20);
	
	// actualizo la imagen
	SDL_BlitSurface(this->arrow->getSDLSurface(), NULL, this->getSDLSurface(), rec);
	SDL_Flip(this->getSDLSurface());
	
}


void UIOptionArrowMenu::arrowDown(){
	
	SDL_Rect* rec = new SDL_Rect();
	rec->h = this->arrow->getHeight();
	rec->w = this->arrow->getWidth();

	
	// borro la flecha anterior
	rec->x = this->arrowX;
	rec->y = this->arrowY;
	SDL_FillRect( this->getSDLSurface(), rec, 0);

	// pongo la flecha en la nueva posicion
	rec->x = this->arrowX;
	rec->y = (this->arrowY+20);

	this->arrowY = (this->arrowY+20);

	// actualizo la imagen
	SDL_BlitSurface(this->arrow->getSDLSurface(), NULL, this->getSDLSurface(), rec);
	SDL_Flip(this->getSDLSurface());
	
}


void UIOptionArrowMenu::notify(SDL_Event e){

	switch(e.type){
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym){
				case SDLK_UP:
					this->arrowUp();
					break;
				case SDLK_DOWN:
					this->arrowDown();
					break;
				case SDLK_RETURN:
					this->addOption("enter");
					this->arrowDown();
					break;
			}
			break;
	}
	

}