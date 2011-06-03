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
	std::string prueba;
public:
	PresentationActivity(int width, int height);
	PresentationActivity(ParameterHolder* params, int width, int height);
	~PresentationActivity();
	void onLoad();
	Activity* notify(SDL_Event e);
};