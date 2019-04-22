#include "p2math.h"

float lerp(const float & origin, const float & end, float by)
{
	if (by > 1.0f) by = 1.0f;
	return origin * (1 - by) + end * by;
}

fPoint lerp(const iPoint & origin, const iPoint & end, const float & by)
{
	return fPoint(lerp(origin.x, end.x, by), lerp(origin.y, end.y, by));
}
