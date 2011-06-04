#pragma once
#include <string>
#include "sdl/SDL.h"
#include "View.h"

class RichTextView: public View{
private:
	int getLetterCount(std::string txt);

public:
	RichTextView(std::string txt, std::string type);
	RichTextView(std::string txt, std::string type, int r, int g, int b, int delta);
	virtual ~RichTextView();
	static std::string MENU_HEADER1;
	static std::string MENU_HEADER2;
	static std::string MENU_ITEM;
	static std::string NORMAL;
};
