#include "StdAfx.h"
#include "GameActivity.h"
#include "Activity.h"

void GameActivity::onLoad(){
	
	// titulo y cabecera
	this->banner = new Image("images/dual.bmp");
	this->title = new RichText("pacman", RichText::NORMAL);
	
	// los agrego a la pantalla
	this->add(this->banner, 0, 0);
	this->add(this->title, 100, 50);
	
}
