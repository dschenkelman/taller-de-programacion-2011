#include "StdAfx.h"
#include "Activity.h"


Activity::Activity() : Image(640,480){
	this->widgets = new List<View*>();
}

Activity::~Activity(){
}


void Activity::init(){
	
	// ejecuta acciones propias de cada actividad
	this->onLoad();
}

void Activity::onLoad(){
}

Activity* Activity::notify(SDL_Event e){
	return NULL;
}


// agrega los widgets a la lista de widgets de la actividad
void Activity::add(View* w){
	this->widgets->add(w);
}

void Activity::update(){
}

// dibuja todos los widgets que fueron agregados
void Activity::drawViews(){
	for(size_t i=0; i < this->widgets->length(); i++){
		
		View* w = this->widgets->at(i);
		
		w->draw();

		SDL_Rect* rec = new SDL_Rect();
		rec->h = w->getHeight();
		rec->w = w->getWidth();
		rec->x = w->getX();
		rec->y = w->getY();
		SDL_BlitSurface(w->getSDLSurface(), NULL, this->getSDLSurface(), rec);
	}
	SDL_Flip(this->getSDLSurface());
}



