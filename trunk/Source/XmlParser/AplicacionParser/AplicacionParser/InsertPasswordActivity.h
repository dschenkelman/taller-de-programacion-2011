#pragma once
#include "Activity.h"
#include "Escenario.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "ImageView.h"

class InsertPasswordActivity : public Activity
{
private:
	ImageView* banner;
	RichTextView* title;
	RichTextView* subtitle;
	RichTextView* passBoxPlayerOne;
	RichTextView* passBoxPlayerTwo;
	RichTextView* msg;
	OptionArrowMenuView* arrowMenu;
	bool boxPlayerOneActive;
	std::string passPlayerOne;
	std::string passPlayerTwo;
	std::string playerOne;
	std::string playerTwo;
	std::string passPlayerOneView;
	std::string passPlayerTwoView;
	char getKey(SDL_KeyboardEvent e);
	std::string getPassword(std::string name);
public:
	InsertPasswordActivity(int width, int height, std::string playerOne, std::string playerTwo);
	void onLoad();
	Activity* notify(SDL_Event e);
};
