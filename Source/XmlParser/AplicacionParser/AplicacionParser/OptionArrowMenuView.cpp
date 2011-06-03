#include "StdAfx.h"
#include "OptionArrowMenuView.h"
#include "RichTextView.h"

OptionArrowMenuView::OptionArrowMenuView(): View(){
	this->options = new List<std::string>();
	this->optionHeight = 17;
	this->arrowX = 0;
	this->arrowY = 0;
	this->arrow = new Image("images/menu-arrow.bmp");

	// la flecha siempre se inicia en la primera opcion
	this->arrowIndex = 1;
}


void OptionArrowMenuView::addOption(std::string optionTxt){
	this->options->add(optionTxt);
}

OptionArrowMenuView::~OptionArrowMenuView()
{
	delete this->arrow;
	delete this->options;
}

// dibujo las opciones del menu
void OptionArrowMenuView::draw(){

	int newH = ( (this->optionHeight+12)*this->options->length() );
	Image* aux = new Image(350, newH);
	this->copy(*aux);
	delete aux;

	// dibujo opciones
	for(size_t i=0; i < this->options->length(); i++){
		RichTextView* newOption = new RichTextView(this->options->at(i), RichTextView::NORMAL);
		SDL_Rect rec;
		rec.h = newOption->getHeight();
		rec.w = newOption->getWidth();
		rec.x = 50;
		rec.y = (this->optionHeight*i);
		SDL_BlitSurface(newOption->getSDLSurface(), NULL, this->getSDLSurface(), &rec);
		delete newOption;
	}
	
	// dibujo flecha
	SDL_Rect rec;
	rec.h = this->arrow->getHeight();
	rec.w = this->arrow->getWidth();
	rec.x = this->arrowX;
	rec.y = this->arrowY;
	SDL_BlitSurface(this->arrow->getSDLSurface(), NULL, this->getSDLSurface(), &rec);

	SDL_Flip(this->getSDLSurface());
}


void OptionArrowMenuView::arrowUp(){
	SDL_Rect rec;
	rec.h = this->arrow->getHeight();
	rec.w = this->arrow->getWidth();

	
	// borro la flecha anterior
	rec.x = this->arrowX;
	rec.y = this->arrowY;
	SDL_FillRect( this->getSDLSurface(), &rec, 0);

	// pongo la flecha en la nueva posicion
	rec.x = this->arrowX;
	if( this->arrowIndex > 1) {
		rec.y = (this->arrowY-this->optionHeight);
		this->arrowY = rec.y;
		this->arrowIndex--;
	} else {
		rec.y = (this->arrowY+this->optionHeight*(this->options->length()-1));
		this->arrowY = rec.y;
		this->arrowIndex+=(this->options->length()-1);
	}
		
		
	// actualizo la imagen
	SDL_BlitSurface(this->arrow->getSDLSurface(), NULL, this->getSDLSurface(), &rec);
	SDL_Flip(this->getSDLSurface());	
}


void OptionArrowMenuView::arrowDown(){
	SDL_Rect rec;
	rec.h = this->arrow->getHeight();
	rec.w = this->arrow->getWidth();
	
	// borro la flecha anterior
	rec.x = this->arrowX;
	rec.y = this->arrowY;
	SDL_FillRect( this->getSDLSurface(), &rec, 0);

	// pongo la flecha en la nueva posicion
	rec.x = this->arrowX;
	if( this->arrowIndex < this->options->length() ){
		rec.y = (this->arrowY+this->optionHeight);
		this->arrowY = rec.y;
		this->arrowIndex++;
	} else {
		rec.y = (this->arrowY-this->optionHeight*(this->options->length()-1));
		this->arrowY = rec.y;
		this->arrowIndex-=this->options->length()-1;
	}

	// actualizo la imagen
	SDL_BlitSurface(this->arrow->getSDLSurface(), NULL, this->getSDLSurface(), &rec);
	SDL_Flip(this->getSDLSurface());
}


std::string OptionArrowMenuView::getSelectedOption(){
	return this->options->at(this->arrowIndex-1);
}


void OptionArrowMenuView::notify(SDL_Event e){

	switch(e.type){
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym){
				case SDLK_UP:
					this->arrowUp();
					break;
				case SDLK_DOWN:
					this->arrowDown();
					break;
			}
			break;
	}
}