#include "StdAfx.h"
#include "CollisionHelper.h"

bool CollisionHelper::AreFullyCollisioned(int x1, int y1, int x2, int y2, int delta)
{
	return abs(x1 - x2) < delta && abs(y1-y2) < delta;
	/*int right1 = left1 + i1->getWidth();
	int bottom1 =  top1 + i1->getHeight();

	int right2 = left2 + i2->getWidth();
	int bottom2 =  top2 + i2->getHeight();

	bool oneCollidedWithTwo = IsPointInRectangle(left1, top1, left2, top2, right2, bottom2) ||
		IsPointInRectangle(right1, top1, left2, top2, right2, bottom2) ||
		IsPointInRectangle(left1, bottom1, left2, top2, right2, bottom2) ||
		IsPointInRectangle(right1, bottom1, left2, top2, right2, bottom2);

	bool twoCollidedWithOne = IsPointInRectangle(left2, top2, left1, top1, right1, bottom1) ||
		IsPointInRectangle(right2, top2, left1, top1, right1, bottom1) ||
		IsPointInRectangle(left2, bottom2, left1, top1, right1, bottom1) ||
		IsPointInRectangle(right2, bottom2, left1, top1, right1, bottom1);

	return oneCollidedWithTwo || twoCollidedWithOne;*/
}

bool CollisionHelper::IsPointInRectangle(int x, int y, int left, int top, int right, int bottom)
{
	return left <= x && x < right && top <= y && y < bottom;
}

bool CollisionHelper::BonusCollision(Image *i1, int left1, int top1, int left2, int top2, int height2, int width2){

	int right1 = left1 + i1->getWidth();
	int bottom1 =  top1 + i1->getHeight();

	int right2 = left2 + width2;
	int bottom2 =  top2 + height2;

	bool oneCollidedWithTwo = IsPointInRectangle(left1, top1, left2, top2, right2, bottom2) ||
		IsPointInRectangle(right1, top1, left2, top2, right2, bottom2) ||
		IsPointInRectangle(left1, bottom1, left2, top2, right2, bottom2) ||
		IsPointInRectangle(right1, bottom1, left2, top2, right2, bottom2);

	bool twoCollidedWithOne = IsPointInRectangle(left2, top2, left1, top1, right1, bottom1) ||
		IsPointInRectangle(right2, top2, left1, top1, right1, bottom1) ||
		IsPointInRectangle(left2, bottom2, left1, top1, right1, bottom1) ||
		IsPointInRectangle(right2, bottom2, left1, top1, right1, bottom1);

	return oneCollidedWithTwo || twoCollidedWithOne;
}