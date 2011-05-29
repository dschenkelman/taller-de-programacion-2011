#pragma once
#include "Image.h"
#include "List.h"
#include "View.h"

class Activity: public Image{
private:
	//EventDispatcher* dispatcher;
	List<View*>* widgets;

public:
	Activity(int width, int height);
	~Activity();
	void add(View* w);
	void init();
	virtual void onLoad();
	virtual Activity* notify(SDL_Event e);
	virtual void update();
	void drawViews();
};