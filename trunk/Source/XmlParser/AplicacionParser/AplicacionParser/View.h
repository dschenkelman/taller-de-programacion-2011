#pragma once
#include "Image.h"

class View: public Image{
private:
	int x;
	int y;
	Image* img;
	int verticalAlign;
public:
	View();
	~View();
	void setX(int x);
	int getX(void);
	void setY(int y);
	int getY(void);
	virtual void draw();
	int getVerticalAlign(void);
	void setVerticalAlign(int value);
	
	// valores de la alineacion
	static const int VERTICAL_ALIGN_CENTER = 1;

};