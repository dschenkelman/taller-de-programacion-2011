#include "StdAfx.h"
#include "ImageView.h"


ImageView::ImageView(std::string uri):View(){
	this->myImg = new Image(uri);
	this->copy(*myImg);
}

ImageView::ImageView(std::string uri, int r, int g, int b, int delta):View(r, g, b, delta){
	this->myImg = new Image(uri);
	this->copy(*myImg);
}

ImageView::~ImageView(){
	delete(this->myImg);
}

void ImageView::draw(){

	SDL_BlitSurface(this->myImg->getSDLSurface(), NULL, this->getSDLSurface(), NULL);
	SDL_Flip(this->getSDLSurface());
}