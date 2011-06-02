#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "ImageView.h"

class StatsActivity : public Activity {
private:
	ImageView* banner;
	RichTextView* title;
	OptionArrowMenuView* arrowMenu;

public:
	void onLoad();
	Activity* notify(SDL_Event e);
	StatsActivity(int width, int height);
	virtual ~StatsActivity();
};