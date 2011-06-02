#pragma once
#include <string>
#include "SDL.h"
#include "View.h"

class RichTextView: public View{

public:
	RichTextView(std::string txt, std::string type);
	~RichTextView();
	static std::string MENU_HEADER1;
	static std::string MENU_HEADER2;
	static std::string MENU_ITEM;
	static std::string NORMAL;
};
