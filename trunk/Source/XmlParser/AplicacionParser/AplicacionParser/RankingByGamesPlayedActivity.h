#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "ImageView.h"

class RankingByGamesPlayedActivity : public Activity
{
private:
	ImageView* banner;
	RichTextView* title;
	OptionArrowMenuView* arrowMenu;
public:
	RankingByGamesPlayedActivity(int width, int height);
	~RankingByGamesPlayedActivity();
	void onLoad();
	Activity* notify(SDL_Event e);
};
