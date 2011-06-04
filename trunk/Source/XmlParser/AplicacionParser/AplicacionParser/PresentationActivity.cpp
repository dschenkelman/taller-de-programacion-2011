#include "StdAfx.h"
#include "PresentationActivity.h"
#include "MenuActivity.h"
#include "Activity.h"


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

	// cabecera
	this->banner = new ImageView("Images/title-pacman.bmp");
	this->banner->setX(0); this->banner->setY(0);
	this->banner->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	int medioX = (this->getWidth()/2);
	int medioY = (this->getHeight()/2);

	ImageView* pc1 = new ImageView("Images/pacman3d.bmp", 255, 255, 255, 20);
	pc1->setX(medioX-100); pc1->setY(140);

	ImageView* pc2 = new ImageView("Images/fantasmaVerde.bmp", 255, 255, 255, 20);
	pc2->setX(medioX+100); pc2->setY(140);


	// menu con flecha
	this->pressEnter = new RichTextView("press enter", RichTextView::NORMAL);
	this->pressEnter->setY(medioY+100);
	this->pressEnter->setVerticalAlign(View::VERTICAL_ALIGN_CENTER);

	// los agrego a la pantalla
	this->add(this->banner);
	this->add(this->pressEnter);
	this->add(pc1);
	this->add(pc2);
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