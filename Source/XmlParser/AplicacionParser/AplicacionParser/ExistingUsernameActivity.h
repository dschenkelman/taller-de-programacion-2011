#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "ImageView.h"

class ExistingUsernameActivity : public Activity
{
private:
	ImageView* banner;
	RichTextView* title;
	OptionArrowMenuView* arrowMenu;
public:
	ExistingUsernameActivity(int width, int height);
	void onLoad();
	Activity* notify(SDL_Event e);
	~ExistingUsernameActivity(void);
};
