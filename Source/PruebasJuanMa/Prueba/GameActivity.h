#pragma once
#include "Activity.h"
#include "RichText.h"
#include "UIOptionArrowMenu.h"

class GameActivity : public Activity {
private:
	Image* banner;
	RichText* title;

public:
	void onLoad();
	void notify(SDL_Event e);
};