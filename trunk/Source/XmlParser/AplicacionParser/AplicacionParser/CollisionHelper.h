#pragma once
#include "Image.h"

class CollisionHelper
{
	public:
	static bool IsPointInRectangle(int x, int y, int left, int top, int right, int bottom);
	static bool AreFullyCollisioned(int left1, int top1, int left2, int top2, int delta);
	static bool BonusCollision(Image *i1, int left1, int top1, int left2, int top2, int height2, int width2);
};
