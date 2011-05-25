#pragma once
#include <string>
#include "sdl/SDL.h"
#include "Image.h"

class RichText{
private:
	Image* txtImg;

public:
	RichText(std::string txt, std::string type);
	~RichText();
	Image* getImage();
	static std::string MENU_HEADER1;
	static std::string MENU_HEADER2;
	static std::string MENU_ITEM;
	static std::string NORMAL;
};
