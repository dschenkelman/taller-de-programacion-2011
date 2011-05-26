#pragma once
#include "Activity.h"
#include "RichText.h"
#include "UIOptionArrowMenu.h"

class MenuActivity : public Activity {
private:
	Image* banner;
	RichText* title;
	UIOptionArrowMenu* arrowMenu;

public:
	void onLoad();
	void notify(SDL_Event e);
};