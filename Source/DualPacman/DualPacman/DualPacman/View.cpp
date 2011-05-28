#include "StdAfx.h"
#include "View.h"


View::View():Image(0,0){
}

View::~View(){
	Image::~Image();
}

void View::setX(int x){
	this->x = x;
}
int View::getX(void){
	return this->x;
}

void View::setY(int y){
	this->y = y;
}
int View::getY(void){
	return this->y;
}

void View::draw(){
}