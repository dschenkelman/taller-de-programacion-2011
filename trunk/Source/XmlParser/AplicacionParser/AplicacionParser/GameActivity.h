#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "Escenario.h"
#include "ScreenManager.h"

class GameActivity : public Activity {
private:
	RichTextView* pointsTitle;
	RichTextView* timeTitle;
	Uint32 period;
	ScreenManager* screenManager;

public:
	GameActivity(int width, int height);
	GameActivity(Escenario* escenario, int width, int height);
	~GameActivity();
	void onLoad();
	Activity* notify(SDL_Event e);
	void update();
};