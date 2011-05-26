#pragma once
#include "Image.h"
#include "List.h"

class UIOptionArrowMenu:public Image{
private:
	int optionsCount;
	Image* arrow;
	int arrowX;
	int arrowY;

public:
	UIOptionArrowMenu();
	~UIOptionArrowMenu();
	void addOption(std::string optionTxt);
	void addListener();
	void notify(SDL_Event e);
	void arrowUp();
	void arrowDown();
};