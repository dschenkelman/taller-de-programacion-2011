#pragma once

class ImageArea
{
	int x;
	int y;
	int imageWidth;
	int imageHeight;
public:
	ImageArea(void);
	ImageArea(int x, int y, int imageW, int imageH);
	int getX();
	int getY();
	int getImageWidth();
	int getImageHeight();
	~ImageArea(void);
};
