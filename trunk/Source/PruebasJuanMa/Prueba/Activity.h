#pragma once
#include "Image.h"

class Activity: public Image{
public:
	Activity();
	~Activity();
	void add(Image* i, int x, int y);
	void init();
	
protected:
	virtual void onLoad();
};