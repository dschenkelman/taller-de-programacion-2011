#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "ImageView.h"

class MenuActivity : public Activity {
private:
	ImageView* banner;
	RichTextView* title;
	OptionArrowMenuView* arrowMenu;

public:
	void onLoad();
	Activity* notify(SDL_Event e);
	MenuActivity(int width, int height);
	MenuActivity(Escenario* escenario, int width, int height);
	~MenuActivity();	
};