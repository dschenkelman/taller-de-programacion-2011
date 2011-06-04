#pragma once
#include "Image.h"

class View: public Image{
private:
	int id;
	int x;
	int y;
	Image* img;
	int verticalAlign;
	int r;
	int g;
	int b;
	int delta;
	bool withAlpha;
public:
	View();
	View(int r, int g, int b, int delta);
	~View();
	void setX(int x);
	int getX(void);
	void setY(int y);
	int getY(void);
	virtual void draw();
	int getVerticalAlign(void);
	void setVerticalAlign(int value);
	void setId(int id);
	int getId(void);

	int getRed(){
		return this->r;
	}
	int getBlue(){
		return this->b;
	}
	int getGreen(){
		return this->r;
	}
	int getDelta(){
		return this->delta;
	}
	bool hasAlpha(){
		return this->withAlpha;
	}
	
	// valores de la alineacion
	static const int VERTICAL_ALIGN_CENTER = 1;

};