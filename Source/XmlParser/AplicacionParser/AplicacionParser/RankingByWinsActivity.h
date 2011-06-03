#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "ImageView.h"

class RankingByWinsActivity : public Activity
{
private:
	ImageView* banner;
	RichTextView* title;
	OptionArrowMenuView* arrowMenu;
public:
	RankingByWinsActivity(int width, int height);
	void onLoad();
	Activity* notify(SDL_Event e);
};
