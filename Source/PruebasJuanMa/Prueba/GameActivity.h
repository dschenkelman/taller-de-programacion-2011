#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"

class GameActivity : public Activity {
private:
	Image* banner;
	RichTextView* title;

public:
	void onLoad();
	Activity* notify(SDL_Event e);
};