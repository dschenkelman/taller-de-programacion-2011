#include "StdAfx.h"
#include "Activity.h"
#include "PixelHelpers.h"

Activity::Activity(int width, int height) : Image(width,height){
	this->widgets = new List<View*>();
}

Activity::Activity(Escenario escenario, int width, int height) : Image(width,height){
	this->widgets = new List<View*>();
	this->escenario = escenario;
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

Escenario Activity::getEscenario(){
	return this->escenario;
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

		if(w->getVerticalAlign() == View::VERTICAL_ALIGN_CENTER){
			rec->x = ((this->getWidth()/2)-(w->getWidth()/2));
		}else{
			rec->x = w->getX();
		}
		rec->y = w->getY();
		
		SDL_BlitSurface(w->getSDLSurface(), NULL, this->getSDLSurface(), rec);
	}
	SDL_Flip(this->getSDLSurface());
}


void Activity::display(Image* image, int x, int y, int red, int green, int blue, int delta)
{
	for (int i = 0; i < image->getWidth(); i++)
	{
		for (int j = 0; j < image->getHeight(); j++)
		{
			Uint32 overPixel = image->getPixel(i, j);
			int deltaPixel = PixelHelpers::getDeltaBetweenPixels(red, green, blue, overPixel);
			if (deltaPixel > delta)
			{
				if (x + i < this->getWidth() && y + j < this->getHeight())
				{
					this->putPixel(overPixel, (x + i), (y + j));
				}
			}
		}
	}
}



void Activity::display(Image* image, int x, int y, int width, int height)
{
	for (int i = x; i < x + width; i++)
	{
		for (int j = y; j < y + height; j++)
		{
			if (i < this->getWidth() && j < this->getHeight())
			{
				Uint32 pixel = image->getPixel(i, j);
				this->putPixel(pixel, i, j);
			}
		}	
	}
}