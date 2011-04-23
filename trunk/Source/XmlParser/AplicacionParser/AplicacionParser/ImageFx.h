#pragma once
#include "Image.h"

class ImageFx
{
public:
	static Image* resize(Image* imgSrc, int widthDst, int heightDst);
	static Image* rotate(Image* imgSrc, int grades);
};