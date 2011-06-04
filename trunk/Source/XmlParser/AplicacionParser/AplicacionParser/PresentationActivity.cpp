#include "StdAfx.h"
#include "PresentationActivity.h"
#include "MenuActivity.h"
#include "Activity.h"
#include <sstream>


PresentationActivity::PresentationActivity(int width, int height):Activity(width, height){
}

PresentationActivity::PresentationActivity(Escenario* escenario, int width, int height):Activity(escenario, width, height){
}

PresentationActivity::PresentationActivity(ParameterHolder* parameters, int width, int height):Activity(parameters, width, height){
}

PresentationActivity::~PresentationActivity(void)
{
	/*delete this->banner;
	delete this->arrowMenu;*/
}


void PresentationActivity::onLoad(){

	//this->setBackgroundImage("images/back_pres_640.bmp");

	// cabecera
	this->banner = new ImageView("Images/title-pacman.bmp",0,0,0,20);
	this->banner->setY(this->getHeight()/9);
	this->banner->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	int medioX = (this->getWidth()/2);
	int medioY = (this->getHeight()/2);

	this->pc3d = new ImageView("Images/pacman3d.bmp", 255, 255, 255, 20);
	pc3d->setX(medioX-100); pc3d->setY(this->getHeight()/4);

	/*ImageView* pc2 = new ImageView("Images/fantasmaVerde.bmp", 255, 255, 255, 20);
	pc2->setX(medioX+100); pc2->setY(140);*/


	// menu con flecha
	this->pressEnter = new RichTextView("press enter", RichTextView::NORMAL);
	this->pressEnter->setY(medioY+100);
	this->pressEnter->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// los agrego a la pantalla
	this->add(this->banner);
	this->add(this->pressEnter);
	this->add(this->pc3d);
	//this->add(pc2);
}

Activity* PresentationActivity::notify(SDL_Event e){

	Activity* nextActivity = NULL;

	switch(e.type){
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym){
				case SDLK_RETURN:
					nextActivity = new MenuActivity(this->getWidth(), this->getHeight());
					break;
			}
			break;
	}

	return nextActivity;
}

void PresentationActivity::update(){
	
	ImageView* pc1 = new ImageView("Images/pacman3d.bmp", 255, 255, 255, 20);
	if(this->pc3d->getX() < (this->getWidth()+25)){
		int newx = this->pc3d->getX()+5;
		pc1->setX(newx); pc1->setY(this->getHeight()/4+10);
		this->updateViewFromView(this->pc3d, pc1);
		delete this->pc3d;
		this->pc3d = pc1;
	}else{
		pc1->setX(-20); pc1->setY(this->getHeight()/4+10);
		this->updateViewFromView(this->pc3d, pc1);
		delete this->pc3d;
		this->pc3d = pc1;
	}


	this->clock++;

}