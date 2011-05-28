#pragma once
#include "Image.h"

class CollisionHelper
{
	static bool IsPointInRectangle(int x, int y, int left, int top, int right, int bottom);
public:
	static bool AreFullyCollisioned(int left1, int top1, int left2, int top2, int delta);
};
