#pragma once
#include "View.h"

class ImageView: public View{
private:
	Image* myImg;
public:
	ImageView(std::string uri);
	ImageView(std::string uri, int r, int g, int b, int delta);
	~ImageView();
	void draw();

};