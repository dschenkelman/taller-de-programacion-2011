#pragma once
#include "Image.h"

class View: public Image{
private:
	int x;
	int y;
	Image* img;
public:
	View();
	~View();
	void setX(int x);
	int getX(void);

	void setY(int y);
	int getY(void);

	virtual void draw();
};