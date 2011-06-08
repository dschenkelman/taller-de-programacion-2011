#pragma once
#include "Activity.h"
#include "RichTextView.h"
#include "OptionArrowMenuView.h"
#include "ImageView.h"
#include "query.h"

typedef struct 
{
public:
	std::string playerOne;
	std::string playerTwo;
	std::string winner;
	int pointsOne;
	int pointsTwo;
	int time;
} game;

class ComparisonBetweenPlayersActivity : public Activity
{
private:
	ImageView* banner;
	RichTextView* title;
	OptionArrowMenuView* arrowMenu;
	std::string playerOne;
	std::string playerTwo;
	int gameNumber;
	void updateAttributes(bool next);
	std::string pointsPlayerOne;
	std::string pointsPlayerTwo;
	std::string time;
	std::string winner;
	void updateRTV();
	RichTextView* pointsPlayerOneRTV;
	RichTextView* pointsPlayerTwoRTV;
	RichTextView* timeRTV;
	RichTextView* winnerRTV;
	RichTextView* gameNumberRTV;
	bool initializeAttributes();
	List<game> gamesList;

public:
	ComparisonBetweenPlayersActivity(int width, int height, std::string playerOne, std::string playerTwo);
	void onLoad();
	Activity* notify(SDL_Event e);
	~ComparisonBetweenPlayersActivity(void);
};
