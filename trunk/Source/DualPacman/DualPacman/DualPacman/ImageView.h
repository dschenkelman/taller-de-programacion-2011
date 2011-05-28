#pragma once
#include "View.h"

class ImageView: public View{
private:
	Image* myImg;
public:
	ImageView(std::string uri);
	~ImageView();
	void draw();

};