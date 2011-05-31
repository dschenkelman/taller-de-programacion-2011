#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "ImageView.h"

class PresentationActivity : public Activity {
private:
	ImageView* banner;
	RichTextView* insertCoin;
	OptionArrowMenuView* arrowMenu;

public:
	PresentationActivity(int width, int height);
	PresentationActivity(Escenario escenario, int width, int height);
	~PresentationActivity();
	void onLoad();
	Activity* notify(SDL_Event e);
};