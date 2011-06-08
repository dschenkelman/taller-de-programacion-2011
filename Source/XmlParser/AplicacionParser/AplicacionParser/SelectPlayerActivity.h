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
	bool game;
	int playersQty;
	RichTextView* returnToMenu;
public:
	SelectPlayerActivity(int width, int height, Escenario* escenario, bool game);
	SelectPlayerActivity(int width, int height, bool game);
	void onLoad();
	Activity* notify(SDL_Event e);
	~SelectPlayerActivity(void);
};
