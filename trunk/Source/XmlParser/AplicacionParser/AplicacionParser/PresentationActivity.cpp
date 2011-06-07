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

	this->clock = 0;

	// cabecera
	this->dual = new ImageView("Images/animate/dual_1.bmp");
	this->dual->setY(this->getHeight()/20);
	this->dual->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	this->banner = new ImageView("Images/title_pacman_big.bmp");
	this->banner->setY(this->getHeight()/9);
	this->banner->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	int medioX = (this->getWidth()/2);
	int medioY = (this->getHeight()/2);

	this->pc3d = new ImageView("Images/pacman3d.bmp", 255, 255, 255, 20);
	pc3d->setX(medioX-100); pc3d->setY(this->getHeight()/4);

	// menu con flecha
	this->pressEnter = new RichTextView("press enter", RichTextView::NORMAL);
	this->pressEnter->setY(medioY+100);
	this->pressEnter->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// los agrego a la pantalla
	this->add(this->dual);
	this->add(this->banner);
	this->add(this->pressEnter);
	this->add(this->pc3d);

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
	int medioY = (this->getHeight()/2);
	RichTextView* newP;
	ImageView* newDual;
	switch(this->clock){
		case 5:
			newDual = new ImageView("Images/animate/dual_2.bmp");
			newDual->setY(this->getHeight()/20);
			newDual->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);
			this->updateViewFromView(this->dual, newDual);
			delete this->dual;
			this->dual = newDual;
			break;
		case 10:
			newP = new RichTextView("press enter", RichTextView::NORMAL_GREEN);
			newP->setY(medioY+100);
			newP->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);
			this->updateViewFromView(this->pressEnter, newP);
			delete this->pressEnter;
			this->pressEnter = newP;
			break;
		case 15:
			newDual = new ImageView("Images/animate/dual_3.bmp");
			newDual->setY(this->getHeight()/20);
			newDual->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);
			this->updateViewFromView(this->dual, newDual);
			delete this->dual;
			this->dual = newDual;
			break;
		case 20:
			newP = new RichTextView("press enter", RichTextView::NORMAL);
			newP->setY(medioY+100);
			newP->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);
			this->updateViewFromView(this->pressEnter, newP);
			delete this->pressEnter;
			this->pressEnter = newP;
			break;
		case 25:
			newDual = new ImageView("Images/animate/dual_4.bmp");
			newDual->setY(this->getHeight()/20);
			newDual->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);
			this->updateViewFromView(this->dual, newDual);
			delete this->dual;
			this->dual = newDual;
			break;
		case 35:
			newDual = new ImageView("Images/animate/dual_1.bmp");
			newDual->setY(this->getHeight()/20);
			newDual->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);
			this->updateViewFromView(this->dual, newDual);
			delete this->dual;
			this->dual = newDual;
			this->clock = 0;
			break;
	}

	this->clock++;

}