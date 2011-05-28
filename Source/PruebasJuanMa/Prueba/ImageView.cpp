#include "StdAfx.h"
#include "ImageView.h"


ImageView::ImageView(std::string uri):View(){
	Image::Image(uri);
}

ImageView::~ImageView():~View(){
}
