#pragma once
#include "View.h"
#include "List.h"

class OptionArrowMenuView:public View{
private:
	List<std::string>* options;
	size_t arrowIndex;
	Image* arrow;
	int arrowX;
	int arrowY;
	void increaseSizeForOption();
	int optionHeight;

public:
	OptionArrowMenuView();
	virtual ~OptionArrowMenuView();
	void addOption(std::string optionTxt);
	void addListener();
	void notify(SDL_Event e);
	void arrowUp();
	void arrowDown();
	std::string getSelectedOption();
	void draw();
};