#pragma once
#include "View.h"

class ImageView: public View{
public:
	ImageView(std::string uri);
	~ImageView();
	void draw();

}