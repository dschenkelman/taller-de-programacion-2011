#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "ScreenManager.h"

class GameActivity : public Activity {
private:
	Image* banner;
	RichTextView* title;
	Uint32 period;
	ScreenManager* screenManager;

public:
	void onLoad();
	Activity* notify(SDL_Event e);
	void update();
};