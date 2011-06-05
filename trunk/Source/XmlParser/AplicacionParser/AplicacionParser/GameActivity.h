#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "Escenario.h"
#include "ScreenManager.h"

class GameActivity : public Activity {
private:
	int xCarteles;
	Escenario* escenario;
	Image* fondo;
	RichTextView* points1Title;
	RichTextView* points2Title;
	RichTextView* timeTitle;
	RichTextView* points1View;
	RichTextView* points2View;
	Uint32 period;
	ScreenManager* screenManager;
	bool errorFound;
	int points1;
	int points2;
	void updateScoreBoard(void);
	bool loaded;
	void loadGame(void);
	std::string playerOne;
	std::string playerTwo;
	RichTextView* loadingTxt;
public:
	GameActivity(int width, int height);
	GameActivity(int width, int height, std::string playerOne, std::string playerTwo);
	GameActivity(Escenario* escenario, int width, int height);
	~GameActivity();
	void onLoad();
	Activity* notify(SDL_Event e);
	void update();
};