#pragma once
#include "Image.h"
#include "List.h"
#include "View.h"
#include "Escenario.h"

class Activity: public Image{
private:
	//EventDispatcher* dispatcher;
	List<View*>* widgets;
	Escenario escenario;
public:
	Activity(int width, int height);
	Activity(Escenario escenario, int width, int height);
	~Activity();
	void add(View* w);
	void init();
	virtual void onLoad();
	virtual Activity* notify(SDL_Event e);
	virtual void update();
	void drawViews();
	void display(Image* image, int x, int y, int red, int blue, int green, int delta);
	void display(Image* image, int x, int y, int width, int height);
	Escenario getEscenario();
};