#ifndef _P2Math_H
#define _P2Math_H

#include "p2Point.h"

class Lerp
{
public:
	Lerp() {};
	static float Lerpaso(const float& origin, const float& end, float by)
	{
		if (by > 1.0f) by = 1.0f;
		return origin * (1.0f - by) + end * by;
	}
	static p2Point<float> lerp(const p2Point<int>& origin, const p2Point<int>& end, const float& by)
	{
		return p2Point<float>(Lerpaso((float)origin.x, (float)end.x, by), Lerpaso((float)origin.y, (float)end.y, by));
	}
};

#endif // !P2Math