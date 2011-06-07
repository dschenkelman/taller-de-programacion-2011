#pragma once
#include <string>
#include "sdl/SDL.h"
#include "View.h"

class RichTextView: public View{

public:
	RichTextView(std::string txt, std::string type);
	RichTextView(std::string txt, std::string type, int r, int g, int b, int delta);
	virtual ~RichTextView();
	int getLetterCount(std::string txt);
	static std::string NORMAL_GREEN;
	static std::string NORMAL;
	static std::string NEON;
};