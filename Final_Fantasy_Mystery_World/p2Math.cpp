#include "p2Math.h"
#include "p2Point.h"
#include <math.h>

float lerp(const float & origin, const float & end, float by)
{
	if (by > 1.0f) by = 1.0f;
	return origin * (1.0f - by) + end * by;
}

fPoint lerp(const iPoint & origin, const iPoint & end, const float & by)
{
	return fPoint(lerp((float)origin.x, (float)end.x, by), lerp((float)origin.y, (float)end.y, by));
}