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

	static std::string NORMAL_GREEN;
	static std::string NORMAL;
};