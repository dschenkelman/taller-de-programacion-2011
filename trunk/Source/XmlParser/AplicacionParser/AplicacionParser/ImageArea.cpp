#include "StdAfx.h"
#include "ImageArea.h"

ImageArea::ImageArea(int x,int y, int imageH, int imageW):x(x),y(y),imageHeight(imageH),imageWidth(imageW)
{
}

ImageArea::~ImageArea(void)
{
}

int ImageArea::getX(){
	return this->x;
}
int ImageArea::getY(){
	return this->y;
}
int ImageArea::getImageWidth(){
	return this->imageWidth;

}
int ImageArea::getImageHeight(){
	return this->imageHeight;
}
