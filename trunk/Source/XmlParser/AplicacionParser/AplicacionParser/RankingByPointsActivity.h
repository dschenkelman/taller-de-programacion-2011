#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "ImageView.h"

class RankingByPointsActivity :	public Activity
{
private:
	ImageView* banner;
	RichTextView* title;
	OptionArrowMenuView* arrowMenu;
public:
	RankingByPointsActivity(int width, int height);
	void onLoad();
	Activity* notify(SDL_Event e);
};
