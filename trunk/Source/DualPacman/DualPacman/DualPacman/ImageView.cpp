#include "StdAfx.h"
#include "ImageView.h"


ImageView::ImageView(std::string uri):View(){
	Image::Image(uri);
	this->myImg = new Image(uri);
	this->copy(*myImg);
}

ImageView::~ImageView(){
	//delete(this->img);

}

void ImageView::draw(){

	SDL_BlitSurface(this->myImg->getSDLSurface(), NULL, this->getSDLSurface(), NULL);
	SDL_Flip(this->getSDLSurface());
}