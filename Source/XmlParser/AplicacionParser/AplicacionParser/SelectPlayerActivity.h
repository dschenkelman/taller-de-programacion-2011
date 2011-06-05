#pragma once
#include "Activity.h"
#include "Escenario.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "ImageView.h"

class SelectPlayerActivity : public Activity
{
private:
	ImageView* banner;
	RichTextView* title;
	RichTextView* subtitle;
	OptionArrowMenuView* arrowMenuPlayerOne;
	OptionArrowMenuView* arrowMenuPlayerTwo;
	Escenario* escenario;
	bool menuPlayerOneActive;
	bool menuPlayerTwoActive;

public:
	SelectPlayerActivity(int width, int height, Escenario* escenario);
	SelectPlayerActivity(int width, int height);
	void onLoad();
	Activity* notify(SDL_Event e);
	~SelectPlayerActivity(void);
};
