#include "StdAfx.h"
#include "Activity.h"


Activity::Activity() : Image(639, 479){
	
}

Activity::~Activity(){
}


void Activity::init(){
	this->onLoad();
	SDL_Flip(this->getSDLSurface());
}

void Activity::onLoad(){
}


void Activity::add(Image* i, int x, int y){
	SDL_Rect* rec = new SDL_Rect();
	rec->h = i->getHeight();
	rec->w = i->getWidth();
	rec->x = x;
	rec->y = y;
	SDL_BlitSurface(i->getSDLSurface(), NULL, this->getSDLSurface(), rec);
}