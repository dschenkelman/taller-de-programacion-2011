#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "ImageView.h"

class CreatePlayerActivity : public Activity
{
private:
	std::string name;
	std::string pass;
	std::string passView;
	bool usernameBoxActive;
	ImageView* banner;
	RichTextView* title;
	OptionArrowMenuView* arrowMenu;
	char getKey(SDL_KeyboardEvent e);
	bool verifyUsername(std::string);
public:
	CreatePlayerActivity(int width, int height);
	void onLoad();
	Activity* notify(SDL_Event e);
	~CreatePlayerActivity(void);
};
