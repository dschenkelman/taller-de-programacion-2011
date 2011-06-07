#include "StdAfx.h"
#include "View.h"

//int View::VERTICAL_ALIGN_CENTER = 1;

View::View():Image(0,0){
	this->withAlpha = false;
	this->focusable = false;
	this->hasFocus = false;
}

View::View(int r, int g, int b, int delta):Image(0,0){
	this->r = r;
	this->g = g;
	this->b = b;
	this->delta = delta;
	this->withAlpha = true;
	this->focusable = false;
	this->hasFocus = false;
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

void View::setVerticalAlign(int value){
	this->verticalAlign = value;
}

int View::getVerticalAlign(){
	return this->verticalAlign;
}

void View::draw(){
}

int View::getId(void){
	return this->id;
}

void View::setId(int id){
	this->id = id;
}