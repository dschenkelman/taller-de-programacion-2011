#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "ImageView.h"

class ComparisonBetweenPlayersActivity : public Activity
{
private:
	ImageView* banner;
	RichTextView* title;
	OptionArrowMenuView* arrowMenu;
	std::string playerOne;
	std::string playerTwo;
public:
	ComparisonBetweenPlayersActivity(int width, int height, std::string playerOne, std::string playerTwo);
	void onLoad();
	Activity* notify(SDL_Event e);
	~ComparisonBetweenPlayersActivity(void);
};
