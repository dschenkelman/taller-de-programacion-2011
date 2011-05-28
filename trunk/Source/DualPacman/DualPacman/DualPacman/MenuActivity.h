#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"

class MenuActivity : public Activity {
private:
	Image* banner;
	RichTextView* title;
	OptionArrowMenuView* arrowMenu;

public:
	void onLoad();
	Activity* notify(SDL_Event e);
};