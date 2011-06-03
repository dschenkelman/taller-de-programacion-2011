#pragma once
#include <string>
#include "sdl/SDL.h"
#include "View.h"

class RichTextView: public View{

public:
	RichTextView(std::string txt, std::string type);
	virtual ~RichTextView();
	static std::string MENU_HEADER1;
	static std::string MENU_HEADER2;
	static std::string MENU_ITEM;
	static std::string NORMAL;
};