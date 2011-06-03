#pragma once
#include "Image.h"

class View: public Image{
private:
	int x;
	int y;
	Image* img;
	int verticalAlign;
	int id;
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
	void setId(int id);
	int getId(void);
	void updateFrom(View* v);
	
	// valores de la alineacion
	static int VERTICAL_ALIGN_CENTER;

};