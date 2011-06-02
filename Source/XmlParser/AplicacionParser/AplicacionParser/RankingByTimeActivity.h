#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "ImageView.h"


class RankingByTimeActivity : public Activity
{
private:
	ImageView* banner;
	RichTextView* title;
	OptionArrowMenuView* arrowMenu;
public:
	RankingByTimeActivity(int width, int height);
	void onLoad();
	Activity* notify(SDL_Event e);
	~RankingByTimeActivity();
};
